//
// Created by jesse on 02/11/2023.
//

#include <Components/ChildComponent.hpp>
#include <Components/ParentComponent.hpp>
#include "EngineManagers/SceneManager.hpp"
#include "Objects/Scene.hpp"
#include "../GameObjectConverter.hpp"
#include "../../src/includes/SystemManager.hpp"

SceneManager SceneManager::instance;

void SceneManager::setActiveScene() {
    if(switchingScene == nullptr)
        return;

    EntityManager::getInstance().clearAllEntities();
    SystemManager::getInstance().clearSystemsCache();

    for (auto camera: switchingScene->getAllCameras())
        GameObjectConverter::addGameObject(camera);

    for (auto gameObject: switchingScene->getAllGameObjects()) {
        GameObjectConverter::addGameObject(gameObject);
    }

    activeSceneSignature = switchingScene->getSignature();
    delete switchingScene;
    switchingScene = nullptr;
}

SceneManager &SceneManager::getInstance() {
    return instance;
}

std::string SceneManager::getActiveSceneSignature() {
    return activeSceneSignature;
}

std::vector<GameObject> SceneManager::getGameObjectsByName(const std::string &name) {
    return GameObjectConverter::getGameObjectsByName(name);
}

std::vector<GameObject *> SceneManager::getGameObjectsByTag(const std::string &tag) {
    return GameObjectConverter::getGameObjectsByTag(tag);
}

Vector2 SceneManager::getWorldPosition(const TransformComponent &transformComponent) {
    auto position = *transformComponent.position;
    try {
        auto parentId = ComponentStore::GetInstance().tryGetComponent<ParentComponent>(
                transformComponent.entityID).parentId;
        auto &parentTransform = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(parentId);
        position += getWorldPosition(parentTransform);
        return position;
    }
    catch (std::runtime_error &e) {
        return position;
    }
}

void SceneManager::goToNewScene(Scene* scene) {
    switchingScene = scene;
}
