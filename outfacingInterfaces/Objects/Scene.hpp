//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_SCENE_HPP
#define BRACK_ENGINE_SCENE_HPP


#include <memory>
#include "GameObject.hpp"
#include "Camera.hpp"
#include "EngineManagers/SceneManager.hpp"

class Scene {
public:
    Scene(Camera &&mainCamera);

    Scene();

    ~Scene() = default;

    void AddGameObject(std::unique_ptr<GameObject> gameObject);

    std::unique_ptr<GameObject>& GetGameObjectByName(char *name);

    std::vector<GameObject*> GetGameObjectsByTag(const std::string& tag);

    std::vector<GameObject*> GetAllGameObjects();

    void RemoveGameObject(GameObject &gameObject);

    Camera &GetMainCamera();

    void SetCamera(Camera &camera);

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    Camera mainCamera;
};


#endif //BRACK_ENGINE_SCENE_HPP
