//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_GAMEOBJECT_HPP
#define BRACK_ENGINE_GAMEOBJECT_HPP


#include "Components/IComponent.hpp"
#include <vector>
#include <string>

class GameObject {
public:
    GameObject() = default;

    ~GameObject() = default;

    template<typename T>
    void AddComponent(T &component) {
        components.push_back(component);
    }

    template<typename T>
    bool HasComponent(T &component) {
        for(auto &comp : components) {
            if(dynamic_cast<T>(comp))
                return true;
        }
        return false;
    }

    template<typename T>
    T *GetComponent(T &component) {
        for(auto &comp : components) {
            if(dynamic_cast<T>(comp))
                return comp;
        }
        return nullptr;
    }

    GameObject &GetParent();

    std::vector<GameObject> GetChildren();

    std::string GetName();

    void SetName(char *name);

    std::string GetTag();

    void SetTag(char *tag);

    bool IsActive();

    void SetActive(bool active);

    int GetLayer();

    void SetLayer(int layer);

    uint32_t GetEntityID();

    void SetEntityID(uint32_t id);

    std::vector<IComponent> GetAllComponents();

protected:
    uint32_t entityID = 0;
    std::vector<IComponent> components;
};


#endif //BRACK_ENGINE_GAMEOBJECT_HPP
