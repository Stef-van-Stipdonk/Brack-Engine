//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_SCENEMANAGER_HPP
#define BRACK_ENGINE_SCENEMANAGER_HPP


#include "Objects/Scene.hpp"

class SceneManager {
public:
    SceneManager() = default;

    ~SceneManager() = default;

    void SetActiveScene(Scene &scene);

private:
    bool hasChanged;
};


#endif //BRACK_ENGINE_SCENEMANAGER_HPP
