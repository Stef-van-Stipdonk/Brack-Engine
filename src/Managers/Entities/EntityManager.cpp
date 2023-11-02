//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include "../../includes/EntityManager.hpp"

uint32_t EntityManager::CreateEntity() {
    uint32_t id = nextID++;
    entities.insert(id);
    return id;
}

void EntityManager::DestroyEntity(uint32_t entity) {
    entities.erase(entity);
}

const std::unordered_set<uint32_t> &EntityManager::GetAllEntities() const {
    return entities;
}

void EntityManager::Initialize() {

}
