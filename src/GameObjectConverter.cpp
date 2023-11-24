//
// Created by jesse on 04/11/2023.
//

#include "GameObjectConverter.hpp"
#include "includes/EntityManager.hpp"
#include "Components/ComponentVisitor.hpp"

Camera GameObjectConverter::getMainCamera(uint32_t entityID) {
    return {};
}

GameObject GameObjectConverter::getGameObject(uint32_t entityID) {
    return {};
}

void GameObjectConverter::addGameObject(GameObject *gameObject) {
    ComponentVisitor componentVisitor;
    auto &components = gameObject->GetAllComponents();
    if (gameObject->GetEntityID() == 0)
        gameObject->SetEntityID(EntityManager::getInstance().createEntity());
    for (auto &component: components) {
        component->entityID = gameObject->GetEntityID();
        component->accept(componentVisitor);
    }
}


void GameObjectConverter::addCamera(Camera *camera) {
    ComponentVisitor componentVisitor;
    if (camera->GetEntityID() == 0)
        camera->SetEntityID(EntityManager::getInstance().createEntity());
    for (auto &component: camera->GetAllComponents()) {
        component->entityID = camera->GetEntityID();
        component->accept(componentVisitor);
    }

}

std::optional<GameObject> GameObjectConverter::getGameObjectByName(const std::string &name) {
    auto entityId = EntityManager::getInstance().getEntityByName(name);
    if (entityId == 0)
        return std::nullopt;

    auto gameObject = GameObject();
    gameObject.SetEntityID(entityId);
    return gameObject;
}

std::vector<GameObject> GameObjectConverter::getGameObjectsByName(const std::string &name) {
    auto gameObjects = std::vector<GameObject>();
    auto entityIds = EntityManager::getInstance().getEntitiesByName(name);
    for (auto entityId: entityIds) {
        auto gameObject = GameObject();
        gameObject.SetEntityID(entityId);
        gameObjects.push_back(gameObject);
    }
    return gameObjects;
}

std::optional<GameObject> GameObjectConverter::getGameObjectByTag(const std::string &tag) {
    auto entityId = EntityManager::getInstance().getEntityByTag(tag);
    if (entityId == 0)
        return std::nullopt;

    auto gameObject = GameObject();
    gameObject.SetEntityID(entityId);
    return gameObject;
}

std::vector<GameObject> GameObjectConverter::getGameObjectsByTag(const std::string &tag) {
    auto gameObjects = std::vector<GameObject>();
    auto entityIds = EntityManager::getInstance().getEntitiesByTag(tag);
    for (auto entityId: entityIds) {
        auto gameObject = GameObject();
        gameObject.SetEntityID(entityId);
        gameObjects.push_back(gameObject);
    }
    return gameObjects;
}
