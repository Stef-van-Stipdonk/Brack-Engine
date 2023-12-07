//
// Created by jesse on 31/10/2023.
//

#include <algorithm>
#include "Objects/Scene.hpp"

void Scene::addGameObject(std::unique_ptr<GameObject> gameObject) {
    if (SceneManager::getInstance().getActiveSceneSignature() == signature) {
        GameObjectConverter::addGameObject(gameObject.get());
        return;
    }

    gameObjects.push_back(std::move(gameObject));
}

GameObject *Scene::getGameObjectByName(const std::string name) {
    if (SceneManager::getInstance().getActiveSceneSignature() == signature) {
        auto optional = GameObjectConverter::getGameObjectByName(name);
        if (optional.has_value()) {
            return *optional;
        }
    }

    for (auto &gameObject: gameObjects) {
        if (gameObject->getName() == name)
            return gameObject.get();
    }

    throw std::runtime_error("No GameObject with name " + std::string(name) + " found.");
}

std::vector<GameObject *> Scene::getGameObjectsByTag(const std::string &tag) {
    if (SceneManager::getInstance().getActiveSceneSignature() == signature) {
        return GameObjectConverter::getGameObjectsByTag(tag);
    }

    std::vector<GameObject *> gameObjectsWithTag;
    for (auto &gameObject: gameObjects) {
        if (gameObject->getTag() == tag) {
            gameObjectsWithTag.push_back(gameObject.get());
        }
    }

    return gameObjectsWithTag;
}

std::vector<GameObject *> Scene::getAllGameObjects() {
    std::vector<GameObject *> gameObjectsPtrs;
    for (auto &gameObject: gameObjects) {
        gameObjectsPtrs.push_back(gameObject.get());
    }
    return gameObjectsPtrs;
}

std::vector<Camera *> Scene::getAllCameras() {
    std::vector<Camera *> camerasPtrs;
    for (auto &camera: cameras) {
        camerasPtrs.push_back(camera.get());
    }
    return camerasPtrs;
}

void Scene::removeGameObjectByName(std::string name) {
    auto gameObject = getGameObjectByName(name);

    if (SceneManager::getInstance().getActiveSceneSignature() == signature) {
        GameObjectConverter::removeGameObject(gameObject);
        return;
    }

    auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
                           [&gameObject](const std::unique_ptr<GameObject> &ptr) {
                               return ptr.get() == gameObject;
                           });
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
    }
}

void Scene::removeGameObject(GameObject &gameObject) {
    if (SceneManager::getInstance().getActiveSceneSignature() == signature) {
        GameObjectConverter::removeGameObject(gameObject);
        return;
    }

    auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
                           [&gameObject](const std::unique_ptr<GameObject> &ptr) {
                               return ptr.get() == &gameObject;
                           });
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
    }
}

Scene::Scene(Camera &&mainCamera) {
    addCamera(std::move(mainCamera));
    signature = generateSignature();
}

Scene::Scene() {
    addCamera(Camera());
    signature = generateSignature();
}

std::vector<std::unique_ptr<Camera>> &Scene::getCameras() {
    return cameras;
}

void Scene::addCamera(Camera &&camera) {
    cameras.push_back(std::make_unique<Camera>(camera));
}

std::string Scene::getSignature() {
    return signature;
}

std::string Scene::generateSignature() {
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < 10; ++i) {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}
