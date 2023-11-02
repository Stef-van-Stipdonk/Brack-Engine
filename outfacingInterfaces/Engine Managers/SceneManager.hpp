//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_SCENEMANAGER_HPP
#define BRACK_ENGINE_SCENEMANAGER_HPP


#include <memory>
#include "../../src/includes/EntityManager.hpp"

class Scene;

class SceneManager {
public:
    SceneManager() = default;

    ~SceneManager() = default;

    void Initialize(std::shared_ptr<EntityManager> newEntityManager);

    void SetActiveScene(Scene &scene);

private:
    std::shared_ptr<EntityManager> entityManager;
    bool hasChanged = false;
};


#endif //BRACK_ENGINE_SCENEMANAGER_HPP
