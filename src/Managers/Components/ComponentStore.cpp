//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include "../../includes/ComponentStore.hpp"
#include "../../includes/SparseSet.hpp"

template<typename T>
void ComponentStore::RemoveComponent(uint32_t entity) {
//    components[std::type_index(typeid(T))].erase(entity);
}

template <typename T>
void ComponentStore::addComponent(uint32_t e, T component) {
    auto it = storages.find(typeid(T));
    if (it != storages.end()) {
        static_cast<SparseSet<T>*>(it->second)->Insert(e, component);
    } else {
        auto newStorage = new SparseSet<T>();
        newStorage->Insert(e, component);
        storages[typeid(T)] = newStorage;
    }
}


template <typename T>
T* ComponentStore::getComponent(uint32_t e) {
    auto it = storages.find(typeid(T));
    if (it != storages.end()) {
        return static_cast<SparseSet<T>*>(it->second)->Get(e);
    }
    return nullptr;
}

ComponentStore::~ComponentStore() {
    for (auto& pair : storages) {
        delete pair.second;
    }
}

