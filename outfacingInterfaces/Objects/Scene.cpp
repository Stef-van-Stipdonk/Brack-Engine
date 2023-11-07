//
// Created by jesse on 31/10/2023.
//

#include "Scene.hpp"
#include <algorithm>

void Scene::AddGameObject(GameObject &gameObject) {
    gameObjects.push_back(gameObject);
}

GameObject &Scene::GetGameObjectByName(char *name) {
    for (auto &gameObject : gameObjects) {
        if (gameObject.GetName() == name)
            return gameObject;
    }
    //TODO: throw exception
    return *new GameObject();
}

std::vector<GameObject> Scene::GetGameObjectsByTag(char *tag) {
    return std::vector<GameObject>();
}

std::vector<GameObject> Scene::GetAllGameObjects() {
    return gameObjects;
}

void Scene::RemoveGameObject(GameObject &gameObject) {

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

