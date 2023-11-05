//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_COMPONENTSTORE_HPP
#define BRACK_ENGINE_COMPONENTSTORE_HPP

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <stdexcept>
#include <memory>
#include <iostream>
#include "Components/IComponent.hpp"
#include "../../outfacingInterfaces/IComponentStorage.hpp"

// TODO: Kijken of we Bitsets voor components kunnen gebruiken
// Vanuit onze vriend google:
// Each entity can have a bitset representing which components it has. Each component type corresponds to a bit position.
// Systems can then define a signature (also a bitset) of required components.
// This allows quick checks to determine if an entity has a specific set of components, which can be used in combination with other data structures to quickly retrieve the required components.

class ComponentStore {
public:
    static ComponentStore &GetInstance();

    ~ComponentStore();

    template<typename T>
    void RemoveComponent(uint32_t entity);

    template<typename T>
    void addComponent(uint32_t e, T component);

    template<typename T>
    T *getComponent(uint32_t e);

    //Tijdelijke oplossing zonder optimalisatie!!
    template<typename T>
    void AddComponent(uint32_t entity, T *component) {
        auto typeID = std::type_index(typeid(component));
        auto it = components.find(typeID);
        if (it != components.end()) {
            it->second[entity] = component;
        } else {
            auto newStorage = std::unordered_map<uint32_t, IComponent *>();
            std::cout << "add " << typeID.name() << std::endl;
            components[typeID] = newStorage;
        }

    }

    template<typename T>
    std::vector<T &> GetEntitiesWithComponent() {
        auto typeID = std::type_index(typeid(T));
        auto it = components.find(typeID);
        if (it != components.end()) {
            std::vector<T &> entities;
            for (auto &component: it->second) {
                T *derivedComponent = dynamic_cast<T *>(component);
                if (derivedComponent) {
                    entities.push_back(derivedComponent);
                }
            }
            return entities;
        }
        return std::vector<T &>();
    }

    template<typename T>
    T &GetComponent(uint32_t entity) {
        auto typeID = std::type_index(typeid(T));
        std::cout << std::endl;
        std::cout << typeID.name() << std::endl;
        std::cout << "size: " << components.size() << std::endl;
        auto it = components.find(typeID);
        if (it != components.end()) {
            std::cout << "Component found" << std::endl;
            auto &componentMap = it->second;
            auto componentIt = componentMap.find(entity);
            if (componentIt != componentMap.end()) {
                return *dynamic_cast<T *>(componentIt->second);
            }
            std::cout << "Component not found" << std::endl;
        }
        throw std::runtime_error("Component not found");
    }

private:
    static ComponentStore instance;

    ComponentStore() = default;

    std::unordered_map<std::type_index, std::unordered_map<uint32_t, IComponent *>> components;

    std::unordered_map<std::type_index, IComponentStorage *> storages;
};


#endif //BRACK_ENGINE_COMPONENTSTORE_HPP
