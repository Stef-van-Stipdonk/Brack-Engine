//
// Created by jesse on 02/11/2023.
//

#include "EngineManagers/SceneManager.hpp"
#include "Objects/Scene.hpp"
#include "../GameObjectConverter.hpp"

SceneManager SceneManager::instance;

void SceneManager::SetActiveScene(Scene &scene) {
    EntityManager::getInstance().clearAllEntities();
    for (auto camera: scene.GetAllCameras())
        GameObjectConverter::addCamera(camera);

    for (auto gameObject: scene.GetAllGameObjects()) {
        GameObjectConverter::addGameObject(gameObject);
    }
}

SceneManager &SceneManager::GetInstance() {
    return instance;
}
