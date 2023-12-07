//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BEHAVIOURSCRIPT_HPP
#define BRACK_ENGINE_BEHAVIOURSCRIPT_HPP

#include "../outfacingInterfaces/Milliseconds.hpp"
#include "../../src/includes/ComponentStore.hpp"
#include <functional>
#include <optional>

class GameObject;

class BehaviourScript {
public:

    explicit BehaviourScript() = default;


    BehaviourScript(std::remove_reference<struct std::unique_ptr<struct BehaviourScript> &>::type type) {
        entityID = type->entityID;
        isActive = type->isActive;
    }

    virtual ~BehaviourScript() = default;

    BehaviourScript(const BehaviourScript &other) {
        entityID = other.entityID;
        isActive = other.isActive;
    }

    virtual std::unique_ptr<BehaviourScript> clone() const = 0;

    virtual void onStart() {};

    virtual void onUpdate(milliseconds deltaTime) {};

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value, T &>::type
    tryGetComponent() {
        return ComponentStore::GetInstance().tryGetComponent<T>(entityID);
    }


    void setActive(bool active) {
        EntityManager::getInstance().setEntityActive(entityID, active);
        tryGetComponent<ObjectInfoComponent>().isActive = active;
    }

    [[nodiscard]] virtual int getPriority() const {};

    static std::optional<GameObject> getGameObjectByName(const std::string &name);

    static std::vector<GameObject> getGameObjectsByName(const std::string &name);

    static std::optional<GameObject> getGameObjectByTag(const std::string &tag);

    static std::vector<GameObject> getGameObjectsByTag(const std::string &tag);

    std::vector<GameObject> getChildren();

    std::optional<GameObject> getParent();

    bool isActive = true;

    entity entityID;
};


#endif //BRACK_ENGINE_BEHAVIOURSCRIPT_HPP
