//
// Created by jesse on 31/10/2023.
//

#include <Components/ParticleEmitterComponent.hpp>
#include <Components/ParticleComponent.hpp>
#include <Components/RectangleComponent.hpp>
#include <Components/VelocityComponent.hpp>
#include <Components/TransformComponent.hpp>
#include <Components/PersistenceTag.hpp>
#include <Components/RigidBodyComponent.hpp>
#include <Components/BoxCollisionComponent.hpp>
#include "ParticleSystem.hpp"
#include "../includes/ComponentStore.hpp"
#include "../ConfigSingleton.hpp"

ParticleSystem::ParticleSystem() {
    for (int i = 0; i < ConfigSingleton::getInstance().getParticleLimit(); ++i) {
        auto particleEntity = EntityManager::getInstance().createEntity();

        auto particleComponent = std::make_unique<ParticleComponent>();
        auto rectangleComponent = std::make_unique<RectangleComponent>(Vector2(0, 0));
        auto velocityComponent = std::make_unique<VelocityComponent>();
        auto transformComponent = std::make_unique<TransformComponent>();
        auto objectInfoComponent = std::make_unique<ObjectInfoComponent>();
        objectInfoComponent->isActive = false;
        auto boxCollider = std::make_unique<BoxCollisionComponent>(Vector2(1,1));
        boxCollider->isTrigger = true;
        auto rigidBody = std::make_unique<RigidBodyComponent>(CollisionType::DYNAMIC);
        rigidBody->gravityScale = 0.0f;

        ComponentStore::GetInstance().addComponent(particleEntity, std::move(rigidBody));
        ComponentStore::GetInstance().addComponent(particleEntity, std::move(transformComponent));
        ComponentStore::GetInstance().addComponent(particleEntity, std::move(velocityComponent));
        ComponentStore::GetInstance().addComponent(particleEntity, std::move(rectangleComponent));
        ComponentStore::GetInstance().addComponent(particleEntity, std::move(particleComponent));
        ComponentStore::GetInstance().addComponent(particleEntity, std::move(objectInfoComponent));
        ComponentStore::GetInstance().addComponent(particleEntity, std::move(boxCollider));
        ComponentStore::GetInstance().addComponent(particleEntity, std::make_unique<PersistenceTag>());
    }
}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::update(milliseconds deltaTime) {
    updateParticles(deltaTime);
    updateParticleEmitters(deltaTime);
}

void ParticleSystem::updateParticles(milliseconds deltaTime) {
    auto particleIds = ComponentStore::GetInstance().getActiveEntitiesWithComponent<ParticleComponent>();
    for (auto id: particleIds) {
        auto &particleComponent = ComponentStore::GetInstance().tryGetComponent<ParticleComponent>(id);
        if (particleComponent.lifeTime <= 0) {
            auto &objectInfoComponent = ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(id);
            objectInfoComponent.isActive = false;
            EntityManager::getInstance().setEntityActive(id, false);
        } else {
            particleComponent.lifeTime -= deltaTime;
        }
    }
}

void ParticleSystem::updateParticleEmitters(milliseconds deltaTime) {
    auto particleEmitterEntityIds = ComponentStore::GetInstance().getActiveEntitiesWithComponent<ParticleEmitterComponent>();
    for (auto id: particleEmitterEntityIds) {
        auto inactiveParticleIds = ComponentStore::GetInstance().getInactiveEntitiesWithComponent<ParticleComponent>();
        if (inactiveParticleIds.empty()) return;

        auto &particleEmitterComponent = ComponentStore::GetInstance().tryGetComponent<ParticleEmitterComponent>(id);
        auto &particleEmitterTransformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(id);

        size_t availablePosition = 0;
        for (size_t i = 0; i < particleEmitterComponent.activeParticles.size(); ++i) {
            if (particleEmitterComponent.activeParticles[i] <= 0) {
                availablePosition = i;
                break;
            } else {
                particleEmitterComponent.activeParticles[i] -= deltaTime;
            }
        }

        if (particleEmitterComponent.activeParticles[availablePosition] <= 0 &&
            particleEmitterComponent.untilNextEmit <= 0) {
            particleEmitterComponent.untilNextEmit = particleEmitterComponent.emitInterval;
            entity inactiveParticleId = inactiveParticleIds[0];

            auto &particleComponent = ComponentStore::GetInstance().tryGetComponent<ParticleComponent>(
                    inactiveParticleId);
            auto &rectangleComponent = ComponentStore::GetInstance().tryGetComponent<RectangleComponent>(
                    inactiveParticleId);
            auto &velocityComponent = ComponentStore::GetInstance().tryGetComponent<VelocityComponent>(
                    inactiveParticleId);
            auto &transformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(
                    inactiveParticleId);
            auto &objectInfoComponent = ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(
                    inactiveParticleId);
            auto &boxCollisionComponent = ComponentStore::GetInstance().tryGetComponent<BoxCollisionComponent>(inactiveParticleId);

            particleComponent.lifeTime = particleEmitterComponent.lifeTime;

            rectangleComponent.fill = std::make_unique<Color>(*particleEmitterComponent.color);
            rectangleComponent.sortingLayer = particleEmitterComponent.sortingLayer;
            rectangleComponent.orderInLayer = particleEmitterComponent.orderInLayer;
            rectangleComponent.size = std::make_unique<Vector2>(particleEmitterComponent.particleSize);

            boxCollisionComponent.size = std::make_unique<Vector2>(particleEmitterComponent.particleSize);

            velocityComponent.velocity = generateRandomDirection(particleEmitterComponent.speed);

            transformComponent.position = std::make_unique<Vector2>(*particleEmitterTransformComponent.position);

            objectInfoComponent.isActive = true;
            EntityManager::getInstance().setEntityActive(inactiveParticleId, true);

            particleEmitterComponent.activeParticles[availablePosition] = particleEmitterComponent.lifeTime;
        }
        particleEmitterComponent.untilNextEmit -= deltaTime;
    }
}

Vector2 ParticleSystem::generateRandomDirection(float speed) {
    // Use a random device to seed the random number engine
    std::random_device rd;

    // Use the Mersenne Twister engine for random number generation
    std::mt19937 gen(rd());

    // Generate a random angle in radians
    std::uniform_real_distribution<float> dis(0, 2 * M_PI);
    double angle = dis(gen);

    // Calculate the x and y components of the velocity vector
    double velocity_x = speed * cos(angle);
    double velocity_y = speed * sin(angle);

    return Vector2(velocity_x, velocity_y);
}

const std::string ParticleSystem::getName() const {
    return "ParticleSystem";
}

void ParticleSystem::cleanUp() {

}

void ParticleSystem::clearCache() {

}
