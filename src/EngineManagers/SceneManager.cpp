//
// Created by jesse on 02/11/2023.
//

#include <iostream>
#include "EngineManagers/SceneManager.hpp"
#include "Objects/Scene.hpp"
#include "../GameObjectConverter.hpp"

SceneManager SceneManager::instance;

void SceneManager::SetActiveScene(Scene &scene) {
    auto camera = scene.GetMainCamera();
    GameObjectConverter::AddCamera(camera);
}

SceneManager &SceneManager::GetInstance() {
    return instance;
}
