//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_SCENE_HPP
#define BRACK_ENGINE_SCENE_HPP


#include <memory>
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Engine Managers/SceneManager.hpp"

class Scene {
public:
    Scene(std::weak_ptr<SceneManager> sceneManager, Camera &&mainCamera);

    Scene(std::weak_ptr<SceneManager> sceneManager);

    ~Scene() = default;

    void AddGameObject(GameObject &gameObject);

    GameObject &GetGameObjectByName(char *name);

    std::vector<GameObject> GetGameObjectsByTag(char *tag);

    std::vector<GameObject> GetAllGameObjects();

    void RemoveGameObject(GameObject &gameObject);

    Camera GetMainCamera();

    void SetCamera(Camera &camera);

private:
    std::weak_ptr<SceneManager> sceneManager;
};


#endif //BRACK_ENGINE_SCENE_HPP
