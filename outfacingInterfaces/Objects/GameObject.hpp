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

class GameObject {
public:
    GameObject();

    ~GameObject() {
        components.clear();
    };

    GameObject& operator=(const GameObject &other) {
        if (this != &other) {
            entityID = other.entityID;
            components.clear();
            for (const auto &comp : other.components) {
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
    void AddComponent(std::unique_ptr<T> component) {
        components.push_back(std::move(component));
    }

    AddComponent(T component){
        AddComponent(std::make_unique<T>(component));
    }
    GameObject(const GameObject &other) {
        entityID = other.entityID;
        components = std::vector<std::unique_ptr<IComponent>>();
        for (auto &comp : other.components) {
            components.push_back(comp->clone());
        }
    }

    template<typename T>
    bool HasComponent(T &component) {
        for (auto &comp: components) {
            if (dynamic_cast<T>(comp))
                return true;
        }
        return false;
    }

    template<typename T>
    T& TryGetComponent() const {
        for (const auto &comp : components) {
            if (auto castedComp = dynamic_cast<T*>(comp.get())) {
                return *castedComp; // dereference the pointer to return a reference
            }
        }
        throw std::runtime_error("Component not found"); // throw an exception if not found
    }

    template<typename T>
    void RemoveComponent() {
        for (auto it = components.begin(); it != components.end();) {
            T* comp = dynamic_cast<T*>(it->get());
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

    uint32_t GetEntityID() const;

    void SetEntityID(uint32_t id);

    std::vector<std::unique_ptr<IComponent>>&GetAllComponents();

protected:
    uint32_t entityID = 0;
    std::vector<std::unique_ptr<IComponent>> components;
};


#endif //BRACK_ENGINE_GAMEOBJECT_HPP
