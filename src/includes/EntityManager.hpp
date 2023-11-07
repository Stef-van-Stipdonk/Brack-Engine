//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ENTITYMANAGER_HPP
#define BRACK_ENGINE_ENTITYMANAGER_HPP


#include <unordered_set>
#include <cstdint>

class EntityManager {

public:
    static EntityManager &GetInstance();

    ~EntityManager() = default;

    EntityManager(const EntityManager &) = delete;

    EntityManager &operator=(const EntityManager &) = delete;

    EntityManager(EntityManager &&) = delete;

    EntityManager &operator=(EntityManager &&) = delete;

    uint32_t CreateEntity();

    void DestroyEntity(uint32_t entity);

    const std::unordered_set<uint32_t> &GetAllEntities() const;

    void ClearAllEntities();


private:
    static EntityManager instance;

    EntityManager() = default;

    std::unordered_set<uint32_t> entities;
    uint32_t nextID = 1; // Start from 1 for simplicity.
};


#endif //BRACK_ENGINE_ENTITYMANAGER_HPP
