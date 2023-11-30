//
// Created by jesse on 31/10/2023.
//

#include <Components/ParticleEmitterComponent.hpp>
#include <Components/ParticleComponent.hpp>
#include <Components/RectangleComponent.hpp>
#include <Components/VelocityComponent.hpp>
#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::update(milliseconds deltaTime) {
    auto particleIds = ComponentStore::GetInstance().getEntitiesWithComponent<ParticleComponent>();
    for (auto id: particleIds) {
        auto& particleComponent = ComponentStore::GetInstance().tryGetComponent<ParticleComponent>(id);
        if(particleComponent.lifeTime <= 0){
            ComponentStore::GetInstance().removeComponent<ParticleComponent>(id);
            ComponentStore::GetInstance().removeComponent<TransformComponent>(id);
            ComponentStore::GetInstance().removeComponent<VelocityComponent>(id);
            ComponentStore::GetInstance().removeComponent<RectangleComponent>(id);
            EntityManager::getInstance().destroyEntity(id);
        }else{
            particleComponent.lifeTime -= deltaTime;
        }
    }

    auto particleEmitterEntityIds = ComponentStore::GetInstance().getEntitiesWithComponent<ParticleEmitterComponent>();
    for (auto id: particleEmitterEntityIds) {
        auto& particleEmitterComponent = ComponentStore::GetInstance().tryGetComponent<ParticleEmitterComponent>(id);
        auto& particleEmitterTransformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(id);
        size_t availablePosition = 0;
        for (size_t i = 0; i < particleEmitterComponent.activeParticles.size(); ++i) {
            if (particleEmitterComponent.activeParticles[i] <= 0) {
                availablePosition = i;
            }else{
                particleEmitterComponent.activeParticles[i] -= deltaTime;
            }
        }

        if(particleEmitterComponent.activeParticles[availablePosition] <= 0 && particleEmitterComponent.untilNextEmit <= 0){
            particleEmitterComponent.untilNextEmit = particleEmitterComponent.emitInterval;
            auto particleEntity = EntityManager::getInstance().createEntity();
            auto particleComponent = std::make_unique<ParticleComponent>();
            particleComponent->lifeTime = particleEmitterComponent.lifeTime;

            auto rectangleComponent = std::make_unique<RectangleComponent>(particleEmitterComponent.particleSize);
            rectangleComponent->fill = std::make_unique<Color>(*particleEmitterComponent.color);

            auto velocityComponent = std::make_unique<VelocityComponent>();
            velocityComponent->velocity = generateRandomDirection(particleEmitterComponent.speed);

            auto transformComponent = std::make_unique<TransformComponent>();
            transformComponent->position = std::make_unique<Vector2>(particleEmitterTransformComponent.position->getX(), particleEmitterTransformComponent.position->getY());

            ComponentStore::GetInstance().addComponent(particleEntity, std::move(transformComponent));
            ComponentStore::GetInstance().addComponent(particleEntity, std::move(velocityComponent));
            ComponentStore::GetInstance().addComponent(particleEntity, std::move(rectangleComponent));
            ComponentStore::GetInstance().addComponent(particleEntity, std::move(particleComponent));

            particleEmitterComponent.activeParticles.push_back(particleEmitterComponent.lifeTime);
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

