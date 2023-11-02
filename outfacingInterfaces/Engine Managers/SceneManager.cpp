//
// Created by jesse on 02/11/2023.
//

#include "SceneManager.hpp"

SceneManager SceneManager::instance;

void SceneManager::SetActiveScene(Scene &scene) {

}

SceneManager &SceneManager::GetInstance() {
    return instance;
}
