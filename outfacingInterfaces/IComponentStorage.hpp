//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ICOMPONENTSTORAGE_HPP
#define BRACK_ENGINE_ICOMPONENTSTORAGE_HPP

#include <cstdint>

class IComponentStorage {
public:
    virtual ~IComponentStorage() = default;

    virtual void RemoveComponentByEntity(uint32_t entity) = 0;

    virtual void InsertComponent(uint32_t entity, void *component) = 0;
};

#endif //BRACK_ENGINE_ICOMPONENTSTORAGE_HPP
