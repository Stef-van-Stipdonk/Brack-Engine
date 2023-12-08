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
#include "../Logger.hpp"
#include "EntityManager.hpp"
#include "../outfacingInterfaces/Components/IBehaviourScript.hpp"


class BehaviourScriptStore {
public:
    BehaviourScriptStore(const BehaviourScriptStore &) = delete;

    BehaviourScriptStore &operator=(const BehaviourScriptStore &) = delete;

    BehaviourScriptStore(BehaviourScriptStore &&) = delete;

    BehaviourScriptStore &operator=(BehaviourScriptStore &&) = delete;

    static BehaviourScriptStore &getInstance();

    ~BehaviourScriptStore() = default;

    template<typename T, typename...Args>
    typename std::enable_if<std::is_base_of<IBehaviourScript, T>::value>::type
    addBehaviourScript(Args &&...args) {
        T script(std::forward<Args>(args)...);
        auto entityId = script.entityID;

        if (entityId == 0)
            throw std::runtime_error(
                    "Entity ID cannot be 0, please make sure to implement a copy constructor for your component of type " +
                    std::string(typeid(T).name()));

        behaviourScripts[entityId].emplace_back(std::make_unique<T>(script));
    }

    template<typename T, typename...Args>
    typename std::enable_if<std::is_base_of<IBehaviourScript, T>::value>::type
    addBehaviourScript(entity entityId, Args &&...args) {
        if (entityId == 0)
            throw std::runtime_error(
                    "Entity ID cannot be 0, please make sure to implement a copy constructor for your component of type " +
                    std::string(typeid(T).name()));

        T script(std::forward<Args>(args)...);
        script.entityID = entityId;

        behaviourScripts[entityId].emplace_back(std::make_unique<T>(script));
    }

    void addBehaviourScript(entity entityId, std::unique_ptr<IBehaviourScript> script) {
        if (entityId == 0)
            throw std::runtime_error("Entity ID cannot be 0.");

        script->entityID = entityId;

        IBehaviourScript &componentRef = *script;

        behaviourScripts[entityId].emplace_back(std::move(script));
    }


    void clearBehaviourScripts() {
        behaviourScripts.clear();
    }

/*    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value, T &>::type
    tryGetBehaviourScript(entity entityId) {
        auto itType = behaviourScripts.find(entityId);
        if (itType != behaviourScripts.end()) {
            // Cast and return a reference to the managed object
            return *static_cast<T *>(itEntity->second.get());

        }
        throw std::runtime_error("Component not found");
    }*/


/*    std::unordered_map<std::type_index, std::unordered_map<entity, std::unique_ptr<BehaviourScript>>>
    getBehaviourScript() {
        std::unordered_map<std::type_index, std::unordered_map<entity, std::unique_ptr<BehaviourScript>>> deepCopy;

        for (auto &[type, entityMap]: behaviourScripts) {
            for (auto &[entityId, component]: entityMap) {
                // Using the clone method to create a deep copy of each component
                deepCopy[type][entityId] = component->clone();
            }
        }

        return deepCopy;
    }*/

    template<typename T>
    typename std::enable_if<std::is_base_of<IBehaviourScript, T>::value>::type
    removeBehaviourScript(entity entityId) {

        auto itType = behaviourScripts.find(entityId);
        if (itType != behaviourScripts.end()) {
            auto itScript = static_cast<T *>(itType->second);
            if (itScript != nullptr) {
                itScript.erase();
            }
        }
    }

    std::vector<std::reference_wrapper<IBehaviourScript>> getAllBehaviourScripts() {
        std::vector<std::reference_wrapper<IBehaviourScript>> result;

        // Iterate through the map
        for (const auto &entry: behaviourScripts) {
            const std::vector<std::unique_ptr<IBehaviourScript>> &scriptVector = entry.second;

            // Iterate through the vector and add references to the result
            for (const auto &scriptPtr: scriptVector) {
                result.push_back(std::ref(*scriptPtr));
            }
        }
        return result;
    }

/*    template<typename T>
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
    }*/


private:
    static BehaviourScriptStore instance;

    BehaviourScriptStore() = default;

    std::map<entity, std::vector<std::unique_ptr<IBehaviourScript>>> behaviourScripts;
};


#endif //BRACKOCALYPSE_BEHAVIOURSCRIPTSTORE_HPP
