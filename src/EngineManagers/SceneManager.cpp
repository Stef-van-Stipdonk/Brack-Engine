//
// Created by jesse on 02/11/2023.
//

#include "EngineManagers/SceneManager.hpp"
#include "Objects/Scene.hpp"
#include "../GameObjectConverter.hpp"

SceneManager SceneManager::instance;

void SceneManager::SetActiveScene(Scene &scene) {
    EntityManager::GetInstance().ClearAllEntities();
    GameObjectConverter::AddCamera(std::move(scene.mainCamera));

    for (auto gameObject: scene.GetAllGameObjects()) {
        GameObjectConverter::AddGameObject(gameObject);
    }
}

SceneManager &SceneManager::GetInstance() {
    return instance;
}
