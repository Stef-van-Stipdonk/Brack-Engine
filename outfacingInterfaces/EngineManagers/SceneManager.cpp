//
// Created by jesse on 02/11/2023.
//

#include <iostream>
#include "SceneManager.hpp"
#include "../outfacingInterfaces/Objects/Scene.hpp"
#include "../../src/GameObjectConverter.hpp"

SceneManager SceneManager::instance;

void SceneManager::SetActiveScene(Scene &scene) {
    auto camera = scene.GetMainCamera();
    GameObjectConverter::AddCamera(camera);
}

SceneManager &SceneManager::GetInstance() {
    return instance;
}
