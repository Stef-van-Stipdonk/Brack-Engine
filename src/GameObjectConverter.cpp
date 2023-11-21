//
// Created by jesse on 04/11/2023.
//

#include "GameObjectConverter.hpp"
#include "includes/EntityManager.hpp"
#include "Components/ComponentVisitor.hpp"

Camera GameObjectConverter::GetMainCamera(uint32_t entityID) {
    return {};
}

GameObject GameObjectConverter::GetGameObject(uint32_t entityID) {
    return {};
}

void GameObjectConverter::AddGameObject(GameObject *gameObject) {
    ComponentVisitor componentVisitor;
    auto &components = gameObject->GetAllComponents();
    if (gameObject->GetEntityID() == 0)
        gameObject->SetEntityID(EntityManager::GetInstance().CreateEntity());
    for (auto &component: components) {
        component->entityID = gameObject->GetEntityID();
        component->Accept(componentVisitor);
    }
}


void GameObjectConverter::AddCamera(Camera *camera) {
    ComponentVisitor componentVisitor;
    if (camera->GetEntityID() == 0)
        camera->SetEntityID(EntityManager::GetInstance().CreateEntity());
    for (auto &component: camera->GetAllComponents()) {
        component->entityID = camera->GetEntityID();
        component->Accept(componentVisitor);
    }
}