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

    void AddComponent(IComponent *component);

    template<typename T>
    T *GetComponent();

    template<typename T>
    bool HasComponent();

    GameObject GetParent();

    std::vector<GameObject> GetChildren();

    std::string GetName();

    void SetName(char *name);

    std::string GetTag();

    void SetTag(char *tag);

    bool IsActive();

    void SetActive(bool active);

    int GetLayer();

    void SetLayer(int layer);
    
private:
    uint32_t entityID;
};


#endif //BRACK_ENGINE_GAMEOBJECT_HPP
