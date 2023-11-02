//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include "../../includes/SparseSet.hpp"

template<typename T>
SparseSet<T>::~SparseSet() {}

template<typename T>
void SparseSet<T>::RemoveComponentByEntity(uint32_t entity) {
    Remove(entity);
}

template<typename T>
void SparseSet<T>::InsertComponent(uint32_t entity, void *component) {
    // Unsafe cast, als iemand iets beters kan vinden <3
    Insert(entity, *static_cast<T *>(component));
}


template<typename T>
void SparseSet<T>::Insert(uint32_t entity, const T &component) {
    if (entity >= sparse.size()) {
        sparse.resize(entity + 1, -1);
    }

    sparse[entity] = dense.size();
    dense.push_back(component);
}

template<typename T>
void SparseSet<T>::Remove(uint32_t entity) {
    if (entity < sparse.size() && sparse[entity] != -1) {
        // Swap remove
        uint32_t lastIndex = dense.size() - 1;
        uint32_t targetIndex = sparse[entity];
        std::swap(dense[targetIndex], dense[lastIndex]);

        uint32_t swappedEntity = sparse[entity];
        sparse[swappedEntity] = targetIndex;

        dense.pop_back();
        sparse[entity] = -1;
    }
}

template<typename T>
T *SparseSet<T>::Get(uint32_t entity) {
    if (entity < sparse.size() && sparse[entity] != -1) {
        return &dense[sparse[entity]];
    }
    return nullptr;
}
