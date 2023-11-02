//
// Created by jesse on 02/11/2023.
//

#include "SceneManager.hpp"

void SceneManager::SetActiveScene(Scene &scene) {

}

void SceneManager::Initialize(std::shared_ptr<EntityManager> newEntityManager) {
    entityManager = newEntityManager;
}
