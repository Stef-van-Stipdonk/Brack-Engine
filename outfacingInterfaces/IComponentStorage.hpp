//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ICOMPONENTSTORAGE_HPP
#define BRACK_ENGINE_ICOMPONENTSTORAGE_HPP

#include <cstdint>
#include "Entity.hpp"

class IComponentStorage {
public:
    virtual ~IComponentStorage() = default;

    virtual void RemoveComponentByEntity(entity entityId) = 0;

    virtual void InsertComponent(entity entityId, void *component) = 0;
};

#endif //BRACK_ENGINE_ICOMPONENTSTORAGE_HPP
