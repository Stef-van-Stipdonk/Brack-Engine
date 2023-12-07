//
// Created by Olaf van den Berg on 07/12/2023.
//

#ifndef BRACKOCALYPSE_BEHAVIOURSCRIPTSTORE_HPP
#define BRACKOCALYPSE_BEHAVIOURSCRIPTSTORE_HPP


#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>
#include <random>
#include <Components/ObjectInfoComponent.hpp>
#include <Components/ParentComponent.hpp>
#include "Components/IComponent.hpp"
#include "../Logger.hpp"
#include "EntityManager.hpp"

class BehaviourScriptStore {
public:
    BehaviourScriptStore(const BehaviourScriptStore &) = delete;

    BehaviourScriptStore &operator=(const BehaviourScriptStore &) = delete;

    BehaviourScriptStore(BehaviourScriptStore &&) = delete;

    BehaviourScriptStore &operator=(BehaviourScriptStore &&) = delete;

    static BehaviourScriptStore &getInstance();

    ~BehaviourScriptStore() = default;

    template<typename T, typename...Args>
    typename std::enable_if<std::is_base_of<IComponent, T>::value>::type
    addBehaviourScript(Args &&...args) {
        T component(std::forward<Args>(args)...);
        auto entityId = component.entityID;

        if (entityId == 0)
            throw std::runtime_error(
                    "Entity ID cannot be 0, please make sure to implement a copy constructor for your component of type " +
                    std::string(typeid(T).name()));

        behaviourScripts[typeid(T)][entityId] = std::make_unique<T>(component);
    }

    template<typename T, typename...Args>
    typename std::enable_if<std::is_base_of<IComponent, T>::value>::type
    addBehaviourScript(entity entityId, Args &&...args) {
        if (entityId == 0)
            throw std::runtime_error(
                    "Entity ID cannot be 0, please make sure to implement a copy constructor for your component of type " +
                    std::string(typeid(T).name()));

        T component(std::forward<Args>(args)...);
        component.entityID = entityId;

        behaviourScripts[typeid(T)][entityId] = std::make_unique<T>(component);
    }

    void addBehaviourScript(entity entityId, std::unique_ptr<IComponent> component) {
        if (entityId == 0)
            throw std::runtime_error("Entity ID cannot be 0.");

        component->entityID = entityId;

        IComponent &componentRef = *component;

        behaviourScripts[typeid(componentRef)][entityId] = std::move(component);
    }


    void clearBehaviourScripts() {
        behaviourScripts.clear();
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value, T &>::type
    tryGetBehaviourScript(entity entityId) {
        auto itType = behaviourScripts.find(typeid(T));
        if (itType != behaviourScripts.end()) {
            auto itEntity = itType->second.find(entityId);
            if (itEntity != itType->second.end()) {
                // Cast and return a reference to the managed object
                return *static_cast<T *>(itEntity->second.get());
            }
        }
        throw std::runtime_error("Component not found");
    }


    std::unordered_map<std::type_index, std::unordered_map<entity, std::unique_ptr<IComponent>>> getBehaviourScript() {
        std::unordered_map<std::type_index, std::unordered_map<entity, std::unique_ptr<IComponent>>> deepCopy;

        for (auto &[type, entityMap]: behaviourScripts) {
            for (auto &[entityId, component]: entityMap) {
                // Using the clone method to create a deep copy of each component
                deepCopy[type][entityId] = component->clone();
            }
        }

        return deepCopy;
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value>::type
    removeBehaviourScript(entity entityId) {
        auto itType = behaviourScripts.find(typeid(T));
        if (itType != behaviourScripts.end()) {
            itType->second.erase(entityId);
        }
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value, std::vector<entity>>::type
    getEntitiesWithBehaviourScript() {
        std::vector<entity> entities;
        auto itType = behaviourScripts.find(typeid(T));
        if (itType != behaviourScripts.end()) {
            for (auto &pair: itType->second) {
                auto &objectInfoComponent = tryGetBehaviourScript<ObjectInfoComponent>(pair.first);
                if (EntityManager::getInstance().isEntityActive(pair.first) && objectInfoComponent.isActive) {
                    entities.push_back(pair.first);
                }
            }
        }
        return entities;
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value, std::vector<entity>>::type
    getInactiveEntitiesWithComponent() {
        std::vector<entity> entities;
        auto itType = behaviourScripts.find(typeid(T));
        if (itType != behaviourScripts.end()) {
            for (auto &pair: itType->second) {
                auto &objectInfoComponent = tryGetBehaviourScript<ObjectInfoComponent>(pair.first);
                if (!EntityManager::getInstance().isEntityActive(pair.first) || !objectInfoComponent.isActive) {
                    entities.push_back(pair.first);
                }
            }
        }
        return entities;
    }


private:
    static BehaviourScriptStore instance;

    BehaviourScriptStore() = default;

    std::map<std::type_index, std::map<entity, std::unique_ptr<IComponent>>> behaviourScripts;
};


#endif //BRACKOCALYPSE_BEHAVIOURSCRIPTSTORE_HPP
