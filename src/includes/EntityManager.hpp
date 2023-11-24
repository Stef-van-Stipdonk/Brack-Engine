//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ENTITYMANAGER_HPP
#define BRACK_ENGINE_ENTITYMANAGER_HPP


#include <unordered_set>
#include <map>
#include <vector>
#include <cstdint>
#include "../../outfacingInterfaces/Entity.hpp"

class EntityManager {

public:
    static EntityManager &getInstance();

    ~EntityManager() = default;

    EntityManager(const EntityManager &) = delete;

    EntityManager &operator=(const EntityManager &) = delete;

    EntityManager(EntityManager &&) = delete;

    EntityManager &operator=(EntityManager &&) = delete;

    entity createEntity();

    void destroyEntity(entity entityId);

    const std::unordered_set<entity> &getAllEntities() const;

    void clearAllEntities();

    void addEntityWithName(entity entityId, const std::string &name);

    void addEntityWithTag(entity entityId, const std::string &tag);

    std::vector<entity> getEntitiesByName(const std::string &name) const;

    entity getEntityByName(const std::string &name) const;

    std::vector<entity> getEntitiesByTag(const std::string &tag) const;

    entity getEntityByTag(const std::string &tag) const;

private:
    static EntityManager instance;

    EntityManager() = default;

    std::unordered_set<entity> entities;
    entity nextID = 1; // Start from 1 for simplicity.
    std::map<std::string, std::vector<entity>> entitiesByName;
    std::map<std::string, std::vector<entity>> entitiesByTag;
};


#endif //BRACK_ENGINE_ENTITYMANAGER_HPP
