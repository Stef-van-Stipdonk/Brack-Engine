//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_COMPONENTSTORE_HPP
#define BRACK_ENGINE_COMPONENTSTORE_HPP

#include <unordered_map>
#include <typeindex>
#include "Components/IComponent.hpp"
#include "../../outfacingInterfaces/IComponentStorage.hpp"

// TODO: Kijken of we Bitsets voor components kunnen gebruiken
// Vanuit onze vriend google:
// Each entity can have a bitset representing which components it has. Each component type corresponds to a bit position.
// Systems can then define a signature (also a bitset) of required components.
// This allows quick checks to determine if an entity has a specific set of components, which can be used in combination with other data structures to quickly retrieve the required components.

class ComponentStore {
private:
    std::unordered_map<std::type_index, IComponentStorage*> storages;

public:
    ~ComponentStore();

    template<typename T>
    void RemoveComponent(uint32_t entity);

    template <typename T>
    void addComponent(uint32_t e, T component);

    template<typename T>
    T *getComponent(uint32_t e);
};



#endif //BRACK_ENGINE_COMPONENTSTORE_HPP
