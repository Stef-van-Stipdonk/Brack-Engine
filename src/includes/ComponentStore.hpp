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

    ~ComponentStore() {
        for (auto &pair: components) {
            for (auto &compPair: pair.second) {
                if (compPair.second != nullptr)
                    delete compPair.second;
            }
        }
    }

    template<typename T>
    void addComponent(uint32_t entity, T *component) {
        components[typeid(T)][entity] = std::move(component);
    }

    template<typename T>
    T *getComponent(uint32_t entity) {
        auto itType = components.find(typeid(T));
        if (itType != components.end()) {
            auto itEntity = itType->second.find(entity);
            if (itEntity != itType->second.end()) {
                return static_cast<T *>(itEntity->second);
            }
        }
        return nullptr;
    }

    template<typename T>
    void removeComponent(uint32_t entity) {
        auto itType = components.find(typeid(T));
        if (itType != components.end()) {
            delete itType->second[entity];
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

    int GetRandom(int min, int max) {
        std::random_device rd;
        std::default_random_engine engine{rd()};

        std::uniform_int_distribution<int> distribution{min, max};

        return distribution(engine);
    }

    template<typename T>
    std::vector<T*> GetComponents(uint32_t entity) {
        std::vector<T*> result;
        auto itType = components.find(typeid(T));
        if (itType != components.end()) {
            for (auto &pair : itType->second) {
                auto derivedComponent = dynamic_cast<T*>(pair.second);
                if (derivedComponent) {
                    result.push_back(derivedComponent);
                }
            }
        }
        return result;
    }

private:
    static ComponentStore instance;

    ComponentStore() = default;


    uint32_t i = GetRandom(0, 100);
    std::unordered_map<std::type_index, std::unordered_map<uint32_t, IComponent *>> components = {};
};

#endif // SIMPLE_COMPONENTSTORE_HPP
