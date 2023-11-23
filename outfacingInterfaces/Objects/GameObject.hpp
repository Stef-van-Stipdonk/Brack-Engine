//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_GAMEOBJECT_HPP
#define BRACK_ENGINE_GAMEOBJECT_HPP


#include "Components/IComponent.hpp"
#include <vector>
#include <string>
#include <typeinfo>
#include <stdexcept>
#include "../src/includes/ComponentStore.hpp"
#include "../Entity.hpp"

class GameObject {
public:
    GameObject();

    ~GameObject() {
        components.clear();
    };

    GameObject &operator=(const GameObject &other) {
        if (this != &other) {
            entityID = other.entityID;
            components.clear();
            for (const auto &comp: other.components) {
                components.push_back(comp->clone());
            }
        }
        return *this;
    }

    std::unique_ptr<GameObject> clone() {
        return std::make_unique<GameObject>(*this);
    }

    bool operator==(const GameObject &other) const {
        return (this->entityID == other.entityID); // Assuming 'id' is a unique identifier for GameObjects
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value>::type
    AddComponent(std::unique_ptr<T> component) {
        components.push_back(std::move(component));
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value>::type
    AddComponent(T component) {
        AddComponent(std::make_unique<T>(component));
    }


    GameObject(const GameObject &other) {
        entityID = other.entityID;
        components = std::vector<std::unique_ptr<IComponent>>();
        for (auto &comp: other.components) {
            components.push_back(comp->clone());
        }
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value, bool>::type
    HasComponent(T &component) {
        for (auto &comp: components) {
            if (dynamic_cast<T>(comp))
                return true;
        }
        return false;
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value, T &>::type
    tryGetComponent() const {
        if (entityID == 0) {
            for (const auto &comp: components) {
                if (auto castedComp = dynamic_cast<T *>(comp.get())) {
                    return *castedComp; // dereference the pointer to return a reference
                }
            }
        } else {
            return ComponentStore::GetInstance().tryGetComponent<T>(entityID);
        }

        throw std::runtime_error("Component not found"); // throw an exception if not found
    }

    template<typename T>
    typename std::enable_if<std::is_base_of<IComponent, T>::value>::type
    RemoveComponent() {
        for (auto it = components.begin(); it != components.end();) {
            T *comp = dynamic_cast<T *>(it->get());
            if (comp != nullptr) {
                it = components.erase(it);
            } else {
                ++it;
            }
        }
    }

    GameObject &GetParent();

    std::vector<GameObject> GetChildren();

    std::string GetName() const;

    void SetName(std::string name);

    std::string GetTag() const;

    void SetTag(std::string name);

    bool IsActive() const;

    void SetActive(bool active);

    int GetLayer() const;

    void SetLayer(int layer);

    entity GetEntityID() const;

    void SetEntityID(entity id);

    std::vector<std::unique_ptr<IComponent>> &GetAllComponents();

protected:
    entity entityID = 0;
    std::vector<std::unique_ptr<IComponent>> components;
};


#endif //BRACK_ENGINE_GAMEOBJECT_HPP
