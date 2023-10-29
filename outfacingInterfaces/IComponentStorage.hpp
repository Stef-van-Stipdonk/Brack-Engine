//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ICOMPONENTSTORAGE_HPP
#define BRACK_ENGINE_ICOMPONENTSTORAGE_HPP

#include <cstdint>

class IComponentStorage {
public:
    virtual ~IComponentStorage() = default;

    virtual void removeComponentByEntity(uint32_t entity) = 0;
    virtual void insertComponent(uint32_t entity, void* component) = 0;
};

#endif //BRACK_ENGINE_ICOMPONENTSTORAGE_HPP
