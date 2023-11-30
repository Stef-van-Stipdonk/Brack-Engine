//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include <string>
#include <algorithm>
#include <Components/PersistenceTag.hpp>
#include "../../includes/EntityManager.hpp"
#include "../../includes/ComponentStore.hpp"

EntityManager EntityManager::instance;

entity EntityManager::createEntity() {
    entity id = nextID++;
    entities.insert(id);
    return id;
}

void EntityManager::destroyEntity(entity entityId) {
    entities.erase(entityId);
}

const std::unordered_set<entity> &EntityManager::getAllEntities() const {
    return entities;
}

void EntityManager::clearAllEntities() {
    auto persistanceEntities = ComponentStore::GetInstance().getEntitiesWithComponent<PersistenceTag>();

    std::unordered_set<entity> copyEnt(entities);
    for(auto entity : copyEnt) {
        auto found = std::find(persistanceEntities.begin(), persistanceEntities.end(), entity);
        if(found == persistanceEntities.end()) {
            ComponentStore::GetInstance().removeAllComponents(entity);
            entities.erase(entity);
        }
    }
}


EntityManager &EntityManager::getInstance() {
    return instance;
}

void EntityManager::addEntityWithName(entity entityId, const std::string &name) {
    if (name.empty())
        return;
    if (entitiesByName.find(name) == entitiesByName.end())
        entitiesByName[name] = {entityId};
    else if (std::find(entitiesByName[name].begin(), entitiesByName[name].end(), entityId) ==
             entitiesByName[name].end())
        entitiesByName[name].push_back(entityId);
}

void EntityManager::addEntityWithTag(entity entityId, const std::string &tag) {
    if (tag.empty())
        return;
    if (entitiesByTag.find(tag) == entitiesByTag.end())
        entitiesByTag[tag] = {entityId};
    else if (std::find(entitiesByTag[tag].begin(), entitiesByTag[tag].end(), entityId) == entitiesByTag[tag].end())
        entitiesByTag[tag].push_back(entityId);
}

std::vector<entity> EntityManager::getEntitiesByName(const std::string &name) const {
    if (entitiesByName.find(name) != entitiesByName.end())
        return entitiesByName.at(name);
    return {};
}

entity EntityManager::getEntityByName(const std::string &name) const {
    if (entitiesByName.find(name) != entitiesByName.end())
        return entitiesByName.at(name)[0];
    return 0;
}

std::vector<entity> EntityManager::getEntitiesByTag(const std::string &tag) const {
    if (entitiesByTag.find(tag) != entitiesByTag.end())
        return entitiesByTag.at(tag);
    return {};
}

entity EntityManager::getEntityByTag(const std::string &tag) const {
    if (entitiesByTag.find(tag) != entitiesByTag.end())
        return entitiesByTag.at(tag)[0];
    return 0;
}
