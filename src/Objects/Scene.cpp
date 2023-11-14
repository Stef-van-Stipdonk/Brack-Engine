//
// Created by jesse on 31/10/2023.
//

#include <algorithm>
#include "Objects/Scene.hpp"

void Scene::AddGameObject(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

std::unique_ptr<GameObject>& Scene::GetGameObjectByName(char *name) {
    for (auto &gameObject: gameObjects) {
        if (gameObject->GetName() == name)
            return gameObject;
    }

    throw std::runtime_error("No GameObject with name " + std::string(name) + " found.");
}

std::vector<GameObject*> Scene::GetGameObjectsByTag(const std::string& tag) {
    std::vector<GameObject*> gameObjectsWithTag;
    for (auto &gameObject: gameObjects) {
        if (gameObject->GetTag() == tag) {
            gameObjectsWithTag.push_back(gameObject.get());
        }
    }

    return gameObjectsWithTag;
}

std::vector<GameObject*> Scene::GetAllGameObjects() {
    std::vector<GameObject*> gameObjectsPtrs;
    for (auto &gameObject: gameObjects) {
        gameObjectsPtrs.push_back(gameObject.get());
    }
    return gameObjectsPtrs;
}

void Scene::RemoveGameObject(GameObject &gameObject) {
    auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
                           [&gameObject](const std::unique_ptr<GameObject>& ptr) {
                               return ptr.get() == &gameObject;
                           });
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
    }
}

Camera &Scene::GetMainCamera() {
    if (mainCamera.GetEntityID() == 0)
        return mainCamera;
    mainCamera = Camera();
    return mainCamera;
}

void Scene::SetCamera(Camera &camera) {
    mainCamera = camera;
}

Scene::Scene(Camera &&mainCamera) {
    this->mainCamera = mainCamera;
}

Scene::Scene() {
    mainCamera = Camera();
}

