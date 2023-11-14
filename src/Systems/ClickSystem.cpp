//
// Created by SKIKK on 10/11/2023.
//

#include <EngineManagers/InputManager.hpp>
#include <Helpers/MouseMap.hpp>
#include <Components/BoxCollisionComponent.hpp>
#include <Components/CircleCollisionComponent.hpp>
#include "ClickSystem.hpp"

ClickSystem::ClickSystem() {}

ClickSystem::~ClickSystem() {}

void ClickSystem::Update(float deltaTime) {
    if(!InputManager::GetInstance().IsMouseReleased(LEFT_MOUSE)) return;

    auto& componentStore = ComponentStore::GetInstance();
    auto& mousePosition = InputManager::GetInstance().GetMousePosition();
    auto clickableComponentIds = componentStore.getEntitiesWithComponent<ClickableComponent>();
    for (int entityId: clickableComponentIds) {
        auto* clickableComponent = componentStore.getComponent<ClickableComponent>(entityId);
        if(clickableComponent->disabled) continue;
        CheckBoxCollision(*clickableComponent, mousePosition);
        CheckCircleCollision(*clickableComponent,mousePosition);
    }
}

void ClickSystem::CheckBoxCollision(const ClickableComponent& clickableComponent, const Vector2& mousePosition) {
    auto boxColliderComponent = ComponentStore::GetInstance().getComponent<BoxCollisionComponent>(clickableComponent.entityID);
    if(boxColliderComponent == nullptr) return;
    auto transformComponent = ComponentStore::GetInstance().getComponent<TransformComponent>(clickableComponent.entityID);
    if(
            mousePosition.getX() >= transformComponent->position->getX() &&
            mousePosition.getX() <= transformComponent->position->getX() + boxColliderComponent->size->getX() &&
            mousePosition.getY() >= transformComponent->position->getY() &&
            mousePosition.getY() <= transformComponent->position->getY() + boxColliderComponent->size->getY()
            ){
        clickableComponent.OnClick();
    }
}

void ClickSystem::CheckCircleCollision(const ClickableComponent &clickableComponent, const Vector2 &mousePosition) {
    auto circleCollisionComponent = ComponentStore::GetInstance().getComponent<CircleCollisionComponent>(clickableComponent.entityID);
    if(circleCollisionComponent == nullptr) return;
    auto transformComponent = ComponentStore::GetInstance().getComponent<TransformComponent>(clickableComponent.entityID);
    auto x = mousePosition.getX();
    auto y = mousePosition.getY();
    auto a = circleCollisionComponent->radius->getX();
    auto b = circleCollisionComponent->radius->getY();
    auto h = transformComponent->position->getX() + circleCollisionComponent->radius->getX();
    auto k = transformComponent->position->getY() + circleCollisionComponent->radius->getY();
    // Calculate the left-hand side of the ellipse equation
    double lhs = ((x - h) * (x - h)) / (a * a) + ((y - k) * (y - k)) / (b * b);

    // Check if the point is inside the ellipse
    if(lhs <= 1.0){
        clickableComponent.OnClick();
    }
}

const std::string ClickSystem::GetName() const {
    return "ClickSystem";
}

void ClickSystem::CleanUp() {

}