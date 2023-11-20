//
// Created by jesse on 31/10/2023.
//

#include <Components/CircleCollisionComponent.hpp>
#include "PhysicsSystem.hpp"
#include "../includes/ComponentStore.hpp"

PhysicsSystem::PhysicsSystem() {
}

PhysicsSystem::~PhysicsSystem() {

}

void PhysicsSystem::Update(float deltaTime) {
    auto &compStore = ComponentStore::GetInstance();

    auto circleCollisionComponentIds = compStore.getEntitiesWithComponent<CircleCollisionComponent>();

    std::vector<CircleCollisionComponent *> circleCollisionComponents;

    for (auto circleCollisionComponentId: circleCollisionComponentIds) {
        auto circleCollisionComponent = compStore.tryGetComponent<CircleCollisionComponent>(
                circleCollisionComponentId);

        circleCollisionComponents.push_back(&circleCollisionComponent);
    }
    PhysicsWrapper::GetInstance().addCircles(circleCollisionComponentIds);

    PhysicsWrapper::GetInstance().update();


}

const std::string PhysicsSystem::GetName() const {
    return "PhysicsSystem";
}

void PhysicsSystem::CleanUp() {

}
