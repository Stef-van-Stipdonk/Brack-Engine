//
// Created by jesse on 31/10/2023.
//

#include <algorithm>
#include "Objects/Scene.hpp"

void Scene::AddGameObject(GameObject &gameObject) {
    gameObjects.push_back(gameObject);
}

GameObject &Scene::GetGameObjectByName(char *name) {
    for (auto &gameObject: gameObjects) {
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
    auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
    }
}

Scene::Scene(Camera &&mainCamera) {
    AddCamera(std::move(mainCamera));
}

Scene::Scene() {
    AddCamera(Camera());
}

std::vector<Camera> Scene::GetCameras() {
    return cameras;
}

void Scene::AddCamera(Camera &&camera) {
    cameras.push_back(camera);
}

