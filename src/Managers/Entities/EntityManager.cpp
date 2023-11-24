//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include <string>
#include <algorithm>
#include "../../includes/EntityManager.hpp"

EntityManager EntityManager::instance;

uint32_t EntityManager::createEntity() {
    uint32_t id = nextID++;
    entities.insert(id);
    return id;
}

void EntityManager::destroyEntity(uint32_t entity) {
    entities.erase(entity);
}

const std::unordered_set<uint32_t> &EntityManager::getAllEntities() const {
    return entities;
}

void EntityManager::clearAllEntities() {
    entities.clear();
}


EntityManager &EntityManager::getInstance() {
    return instance;
}

void EntityManager::addEntityWithName(uint32_t entity, const std::string &name) {
    if (name.empty())
        return;
    if (entitiesByName.find(name) == entitiesByName.end())
        entitiesByName[name] = {entity};
    else if (std::find(entitiesByName[name].begin(), entitiesByName[name].end(), entity) == entitiesByName[name].end())
        entitiesByName[name].push_back(entity);
}

void EntityManager::addEntityWithTag(uint32_t entity, const std::string &tag) {
    if (tag.empty())
        return;
    if (entitiesByTag.find(tag) == entitiesByTag.end())
        entitiesByTag[tag] = {entity};
    else if (std::find(entitiesByTag[tag].begin(), entitiesByTag[tag].end(), entity) == entitiesByTag[tag].end())
        entitiesByTag[tag].push_back(entity);
}

std::vector<uint32_t> EntityManager::getEntitiesByName(const std::string &name) const {
    if (entitiesByName.find(name) != entitiesByName.end())
        return entitiesByName.at(name);
    return {};
}

uint32_t EntityManager::getEntityByName(const std::string &name) const {
    if (entitiesByName.find(name) != entitiesByName.end())
        return entitiesByName.at(name)[0];
    return 0;
}

std::vector<uint32_t> EntityManager::getEntitiesByTag(const std::string &tag) const {
    if (entitiesByTag.find(tag) != entitiesByTag.end())
        return entitiesByTag.at(tag);
    return {};
}

uint32_t EntityManager::getEntityByTag(const std::string &tag) const {
    if (entitiesByTag.find(tag) != entitiesByTag.end())
        return entitiesByTag.at(tag)[0];
    return 0;
}
