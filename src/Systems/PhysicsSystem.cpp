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

void PhysicsSystem::update(int deltaTime) {
    handleCircles();
    handleBoxes();

    PhysicsWrapper::getInstance().update(deltaTime);

}

void PhysicsSystem::cleanUp() {

}

const std::string PhysicsSystem::getName() const {
    return "PhysicsSystem";
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

PhysicsSystem::PhysicsSystem(const PhysicsSystem &other) {
    physicsWrapper = std::make_unique<PhysicsWrapper>(*other.physicsWrapper);
}




