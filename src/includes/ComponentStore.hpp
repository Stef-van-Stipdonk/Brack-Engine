#ifndef SIMPLE_COMPONENTSTORE_HPP
#define SIMPLE_COMPONENTSTORE_HPP

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>
#include <random>
#include "Components/IComponent.hpp"
#include "../Logger.hpp"

//// Forward declaration of IComponent
//struct IComponent {
//    virtual ~IComponent() = default;
//};

// Simplified ComponentStore
class ComponentStore {
public:
    ComponentStore(const ComponentStore &) = delete;

    ComponentStore &operator=(const ComponentStore &) = delete;

    ComponentStore(ComponentStore &&) = delete;

    ComponentStore &operator=(ComponentStore &&) = delete;

    static ComponentStore &GetInstance();

    ~ComponentStore() = default;

    template<typename T>
    void addComponent(uint32_t entity, std::unique_ptr<T> component) {
        components[typeid(T)][entity] = std::move(component);
    }

    template<typename T>
    T& tryGetComponent(uint32_t entity) {
        auto itType = components.find(typeid(T));
        if (itType != components.end()) {
            auto itEntity = itType->second.find(entity);
            if (itEntity != itType->second.end()) {
                // Cast and return a reference to the managed object
                return *static_cast<T*>(itEntity->second.get());
            }
        }
        throw std::runtime_error("Component not found");
    }

    template<typename BaseT>
    std::vector<BaseT*> getAllComponentsOfType() {
        std::vector<BaseT*> result;
        for (auto& [type, map] : components) {
            for (auto& [id, comp] : map) {
                BaseT* casted = dynamic_cast<BaseT*>(comp.get());
                if (casted) {
                    result.push_back(casted);
                }
            }
        }
        return result;
    }



    template<typename T>
    void removeComponent(uint32_t entity) {
        auto itType = components.find(typeid(T));
        if (itType != components.end()) {
            itType->second.erase(entity);
        }
    }

    template<typename T>
    std::vector<uint32_t> getEntitiesWithComponent() {
        std::vector<uint32_t> entities;
        auto itType = components.find(typeid(T));
        if (itType != components.end()) {
            for (auto &pair: itType->second) {
                entities.push_back(pair.first);
            }
        }
        return entities;
    }


private:
    static ComponentStore instance;
    ComponentStore() = default;
    std::unordered_map<std::type_index, std::unordered_map<uint32_t, std::unique_ptr<IComponent>>> components;
};

#endif // SIMPLE_COMPONENTSTORE_HPP