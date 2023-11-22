//
// Created by jesse on 31/10/2023.
//

#include <Components/CircleCollisionComponent.hpp>
#include <Components/BoxCollisionComponent.hpp>
#include "PhysicsSystem.hpp"
#include "../includes/ComponentStore.hpp"

PhysicsSystem::PhysicsSystem() {
}

PhysicsSystem::~PhysicsSystem() {

}

void PhysicsSystem::Update(float deltaTime) {
    handleCircles();
    handleBoxes();

    PhysicsWrapper::getInstance().update(deltaTime);


}

void PhysicsSystem::handleCircles() {
    auto &compStore = ComponentStore::GetInstance();

    auto circleCollisionComponentIds = compStore.getEntitiesWithComponent<CircleCollisionComponent>();

    if (circleCollisionComponentIds.empty()) return;
    PhysicsWrapper::getInstance().addCircles(circleCollisionComponentIds);
}

void PhysicsSystem::handleBoxes() {
    auto &compStore = ComponentStore::GetInstance();

    auto boxCollisionComponentIds = compStore.getEntitiesWithComponent<BoxCollisionComponent>();

    if (boxCollisionComponentIds.empty()) return;
    PhysicsWrapper::getInstance().addBoxes(boxCollisionComponentIds);
}

const std::string PhysicsSystem::GetName() const {
    return "PhysicsSystem";
}

void PhysicsSystem::CleanUp() {

}
