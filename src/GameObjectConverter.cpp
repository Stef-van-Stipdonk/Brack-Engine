//
// Created by jesse on 04/11/2023.
//

#include <iostream>
#include "GameObjectConverter.hpp"
#include "includes/EntityManager.hpp"
#include "includes/ComponentStore.hpp"
#include "Components/CameraComponent.hpp"

Camera GameObjectConverter::GetMainCamera(uint32_t entityID) {
    return Camera();
}

GameObject GameObjectConverter::GetGameObject(uint32_t entityID) {
    return GameObject();
}

void GameObjectConverter::AddGameObject(GameObject &gameObject) {

}

void GameObjectConverter::RemoveGameObject(GameObject &gameObject) {

}

void GameObjectConverter::AddCamera(Camera &camera) {
    camera.SetEntityID(EntityManager::GetInstance().CreateEntity());
    std::cout << camera.GetEntityID() << std::endl;
    auto *cameraComponent = new CameraComponent(camera.GetEntityID());
    cameraComponent->size = camera.GetSize();
    cameraComponent->backgroundColor = camera.GetBackgroundColor();
    ComponentStore::GetInstance().addComponent(camera.GetEntityID(),cameraComponent);
}
