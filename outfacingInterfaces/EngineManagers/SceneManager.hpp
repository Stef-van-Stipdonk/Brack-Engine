//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_SCENEMANAGER_HPP
#define BRACK_ENGINE_SCENEMANAGER_HPP


#include <memory>
#include "../../src/includes/EntityManager.hpp"
#include "../../src/GameObjectConverter.hpp"

class Scene;

class SceneManager {
public:
    static SceneManager &getInstance();

    ~SceneManager() = default;

    SceneManager(const SceneManager &) = delete;

    SceneManager &operator=(const SceneManager &) = delete;

    SceneManager(SceneManager &&) = delete;

    SceneManager &operator=(SceneManager &&) = delete;

    void setActiveScene(Scene &scene);

    static std::optional<GameObject> getGameObjectByName(const std::string &name);

    static std::vector<GameObject> getGameObjectsByName(const std::string &name);

    static std::optional<GameObject> getGameObjectByTag(const std::string &tag);

    static std::vector<GameObject> getGameObjectsByTag(const std::string &tag);

private:
    SceneManager() = default;

    static SceneManager instance;
    bool hasChanged = false;

};


#endif //BRACK_ENGINE_SCENEMANAGER_HPP
