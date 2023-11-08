//
// Created by jesse on 04/11/2023.
//

#include <iostream>
#include "GameObjectConverter.hpp"
#include "includes/EntityManager.hpp"
#include "includes/ComponentStore.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/ComponentVisitor.hpp"

Camera GameObjectConverter::GetMainCamera(uint32_t entityID) {
    return {};
}

GameObject GameObjectConverter::GetGameObject(uint32_t entityID) {
    return {};
}

void GameObjectConverter::AddGameObject(GameObject &gameObject) {
    ComponentVisitor componentVisitor;
    if (gameObject.GetEntityID() == 0)
        gameObject.SetEntityID(EntityManager::GetInstance().CreateEntity());
    for (auto &component: gameObject.GetAllComponents()) {
        component->entityID = gameObject.GetEntityID();
        component->Accept(componentVisitor);
    }
}


void GameObjectConverter::AddCamera(Camera &camera) {
    camera.SetEntityID(EntityManager::GetInstance().CreateEntity());
    auto *cameraComponent = camera.GetCameraComponent();
    camera.SetEntityID(camera.GetEntityID());
    cameraComponent->size = camera.GetSize();
    cameraComponent->backgroundColor = camera.GetBackgroundColor();
    ComponentStore::GetInstance().addComponent(camera.GetEntityID(), cameraComponent);
}
