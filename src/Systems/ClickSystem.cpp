//
// Created by SKIKK on 10/11/2023.
//

#include <EngineManagers/InputManager.hpp>
#include <Helpers/MouseMap.hpp>
#include <Components/ClickableComponent.hpp>
#include <Components/BoxCollisionComponent.hpp>
#include "ClickSystem.hpp"
#include "../includes/ComponentStore.hpp"

ClickSystem::ClickSystem() {}

ClickSystem::~ClickSystem() {}

void ClickSystem::Update(float deltaTime) {
    if(InputManager::GetInstance().IsMouseReleased(LEFT_MOUSE)){
        auto mousePosition = InputManager::GetInstance().GetMousePosition();
        auto clickableComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<ClickableComponent>();
        for (int entityId: clickableComponentIds) {
            auto clickableComponent = ComponentStore::GetInstance().getComponent<ClickableComponent>(entityId);
            if(!clickableComponent->disabled){
                auto boxColliderComponent = ComponentStore::GetInstance().getComponent<BoxCollisionComponent>(entityId);
                auto transformComponent = ComponentStore::GetInstance().getComponent<TransformComponent>(entityId);
                if(
                    mousePosition.getX() >= transformComponent->position->getX() &&
                    mousePosition.getX() <= transformComponent->position->getX() + boxColliderComponent->size->getX() &&
                    mousePosition.getY() >= transformComponent->position->getY() &&
                    mousePosition.getY() <= transformComponent->position->getY() + boxColliderComponent->size->getY()
                ){
                    clickableComponent->OnClick();
                }
            }
        }
    }
}

const std::string ClickSystem::GetName() const {
    return "ClickSystem";
}

void ClickSystem::CleanUp() {

}