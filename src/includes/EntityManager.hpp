//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ENTITYMANAGER_HPP
#define BRACK_ENGINE_ENTITYMANAGER_HPP


#include <unordered_set>
#include <cstdint>

class EntityManager {
private:
    std::unordered_set<uint32_t> entities;
    uint32_t nextID = 1; // Start from 1 for simplicity.

public:
    void Initialize();

    uint32_t CreateEntity();

    void DestroyEntity(uint32_t entity);

    const std::unordered_set<uint32_t> &GetAllEntities() const;
};


#endif //BRACK_ENGINE_ENTITYMANAGER_HPP
