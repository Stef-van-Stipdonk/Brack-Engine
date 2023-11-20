//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ENTITYMANAGER_HPP
#define BRACK_ENGINE_ENTITYMANAGER_HPP


#include <unordered_set>
#include <map>
#include <vector>
#include <cstdint>

class EntityManager {

public:
    static EntityManager &getInstance();

    ~EntityManager() = default;

    EntityManager(const EntityManager &) = delete;

    EntityManager &operator=(const EntityManager &) = delete;

    EntityManager(EntityManager &&) = delete;

    EntityManager &operator=(EntityManager &&) = delete;

    uint32_t createEntity();

    void destroyEntity(uint32_t entity);

    const std::unordered_set<uint32_t> &getAllEntities() const;

    void clearAllEntities();

    void addEntityWithName(uint32_t entity, const std::string &name);

    void addEntityWithTag(uint32_t entity, const std::string &tag);

    std::vector<uint32_t> getEntitiesByName(const std::string &name) const;

    uint32_t getEntityByName(const std::string &name) const;

    std::vector<uint32_t> getEntitiesByTag(const std::string &tag) const;

    uint32_t getEntityByTag(const std::string &tag) const;

private:
    static EntityManager instance;

    EntityManager() = default;

    std::unordered_set<uint32_t> entities;
    uint32_t nextID = 1; // Start from 1 for simplicity.
    std::map<std::string, std::vector<uint32_t>> entitiesByName;
    std::map<std::string, std::vector<uint32_t>> entitiesByTag;
};


#endif //BRACK_ENGINE_ENTITYMANAGER_HPP
