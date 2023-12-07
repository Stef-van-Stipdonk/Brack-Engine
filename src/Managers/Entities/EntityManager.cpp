//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include <string>
#include "../../includes/EntityManager.hpp"

EntityManager EntityManager::instance;

entity EntityManager::createEntity() {
    entity id = nextID++;
    entities.insert(id);
    return id;
}

void EntityManager::destroyEntity(entity entityId) {
    auto name = entityToName.find(entityId);
    nameToEntity.erase(name->second);
    auto tag = entityToTag.find(entityId);
    tagToEntity.erase(name->second);
    entityToTag.erase(entityId);
    entityToName.erase(entityId);
    entities.erase(entityId);
    reserveEntities.push_back(entityId);
}

void EntityManager::addEntitiesByTags(std::map<std::string, std::vector<entity>> entitiesByTag) {
    for (auto &pair: entitiesByTag) {
        for (auto &entity: pair.second) {
            addEntityWithTag(entity, pair.first);
        }
    }
}

void EntityManager::addEntitiesByName(std::map<std::string, std::vector<entity>> entitiesByName) {
    for (auto &pair: entitiesByName) {
        for (auto &entity: pair.second) {
            addEntityWithName(entity, pair.first);
        }
    }
}

const std::unordered_set<entity> &EntityManager::getAllEntities() const {
    return entities;
}

void EntityManager::clearAllEntities() {
    entities.clear();
}


EntityManager &EntityManager::getInstance() {
    return instance;
}

void EntityManager::addEntityWithName(entity entityId, const std::string &name) {
    if (name.empty())
        return;
    if (nameToEntity.find(name) == nameToEntity.end())
        nameToEntity[name] = {entityId};
    else if (std::find(nameToEntity[name].begin(), nameToEntity[name].end(), entityId) ==
             nameToEntity[name].end())
        nameToEntity[name].push_back(entityId);

    entityToName[entityId] = name;
}

void EntityManager::addEntityWithTag(entity entityId, const std::string &tag) {
    if (tag.empty())
        return;
    if (tagToEntity.find(tag) == tagToEntity.end())
        tagToEntity[tag] = {entityId};
    else if (std::find(tagToEntity[tag].begin(), tagToEntity[tag].end(), entityId) == tagToEntity[tag].end())
        tagToEntity[tag].push_back(entityId);

    entityToTag[entityId] = tag;
}

void EntityManager::addEntity(entity entity) {
    entities.insert(entity);
}


std::vector<entity> EntityManager::getEntitiesByName(const std::string &name) const {
    if (nameToEntity.find(name) != nameToEntity.end())
        return nameToEntity.at(name);
    return {};
}

entity EntityManager::getEntityByName(const std::string &name) const {
    if (nameToEntity.find(name) != nameToEntity.end())
        return nameToEntity.at(name)[0];
    return 0;
}

std::vector<entity> EntityManager::getEntitiesByTag(const std::string &tag) const {
    if (tagToEntity.find(tag) != tagToEntity.end())
        return tagToEntity.at(tag);
    return {};
}

entity EntityManager::getEntityByTag(const std::string &tag) const {
    if (tagToEntity.find(tag) != tagToEntity.end())
        return tagToEntity.at(tag)[0];
    return 0;
}

std::map<std::string, std::vector<entity>> EntityManager::getEntitiesByNameMap() const {
    return nameToEntity;
}

std::map<std::string, std::vector<entity>> EntityManager::getEntitiesByTagMap() const {
    return tagToEntity;
}

void EntityManager::setEntitiesByNameMap(const std::map<std::string, std::vector<entity>> &entitiesByName) {
    EntityManager::nameToEntity = entitiesByName;
}

void EntityManager::setEntitiesByTagMap(const std::map<std::string, std::vector<entity>> &entitiesByTag) {
    EntityManager::tagToEntity = entitiesByTag;
}

bool EntityManager::isEntityActive(entity entityID) const {
    auto it = activeEntities.find(entityID);
    if (it != activeEntities.end())
        return activeEntities.at(entityID);
    return false;
}

void EntityManager::setEntityActive(entity entityID, bool active) {
    activeEntities[entityID] = active;
}
