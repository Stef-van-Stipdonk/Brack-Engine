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

    ~Scene() {};

    void addGameObject(std::unique_ptr<GameObject> gameObject);

    GameObject *getGameObjectByName(const std::string name);

    std::vector<GameObject *> getGameObjectsByTag(const std::string &tag);

    std::vector<GameObject *> getAllGameObjects();

    std::vector<Camera *> getAllCameras();

    void removeGameObject(GameObject &gameObject);

    void removeGameObjectByName(std::string name);

    std::vector<std::unique_ptr<Camera>> &getCameras();

    void addCamera(Camera &&camera);

    std::string getSignature();

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::vector<std::unique_ptr<Camera>> cameras;

    std::string generateSignature();

    std::string signature;

};


#endif //BRACK_ENGINE_SCENE_HPP
