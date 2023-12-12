//
// Created by jesse on 31/10/2023.
//

#include <Helpers/Vector2.hpp>
#include <Components/AIComponent.hpp>
#include <Components/TransformComponent.hpp>
#include <Components/VelocityComponent.hpp>
#include "AISystem.hpp"
#include "../includes/ComponentStore.hpp"

AISystem::AISystem() {

}

AISystem::~AISystem() {

}

void AISystem::update(milliseconds deltaTime) {
    auto aiComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<AIComponent>();
    for (auto& aiComponentId: aiComponentIds) {
        auto& aiComponent = ComponentStore::GetInstance().tryGetComponent<AIComponent>(aiComponentId);
        auto& aiTransformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(aiComponentId);
        auto& velocityComponent = ComponentStore::GetInstance().tryGetComponent<VelocityComponent>(aiComponentId);

        if(aiComponent.destination != nullptr && aiComponent.lastCalculated > 0){
            aiComponent.lastCalculated -= deltaTime;
        }

        if(aiComponent.target != nullptr && (aiComponent.destination == aiTransformComponent.position || aiComponent.lastCalculated == 0)){
            aiComponent.lastCalculated = aiComponent.calculatePathInterval;
            aiComponent.destination = std::make_unique<Vector2>(getNextLocation(aiTransformComponent.position, aiComponent.target));
        }

        auto newVelocity = calculateVelocity(aiComponent.destination, aiTransformComponent.position, aiComponent.speed);
        if(velocityComponent.velocity != newVelocity){
            velocityComponent.velocity = newVelocity;
        }
    }
}

Vector2 AISystem::calculateVelocity(const std::unique_ptr<Vector2> &target, const std::unique_ptr<Vector2> &source,
                                    float speed) {
    // Calculate the direction vector
    float dx = target->getX() - source->getX();
    float dy = target->getY() - source->getY();

    // Calculate the length of the direction vector
    float length = std::sqrt(dx * dx + dy * dy);

    // Normalize the direction vector to get a unit vector
    float unit_vector_x = dx / length;
    float unit_vector_y = dy / length;

    // Calculate the velocity vector
    float velocity_x = unit_vector_x * speed;
    float velocity_y = unit_vector_y * speed;

    return {velocity_x, velocity_y};
}
Vector2 AISystem::getNextLocation(const std::unique_ptr<Vector2>& target, const std::unique_ptr<Vector2>& source) {
    
}

const std::string AISystem::getName() const {
    return "AISystem";
}

void AISystem::cleanUp() {

}

void AISystem::clearCache() {

}
