//
// Created by jesse on 31/10/2023.
//

#include <Components/TransformComponent.hpp>
#include <Components/ObjectInfoComponent.hpp>
#include "Objects/GameObject.hpp"

GameObject::GameObject() {
    AddComponent(std::make_unique<TransformComponent>());
    AddComponent(std::make_unique<ObjectInfoComponent>());
}

std::vector<GameObject> GameObject::GetChildren() {
    return std::vector<GameObject>();
}

std::string GameObject::GetName() const{
    if (entityID == 0) {
        return TryGetComponent<ObjectInfoComponent>().name;
    }

    return ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).name;

}


void GameObject::SetName(std::string name) {
    if (entityID == 0) {
        TryGetComponent<ObjectInfoComponent>().name = name;
    } else {
        ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).name = name;
    }
}

std::string GameObject::GetTag() const{
    if (entityID == 0) {
        return TryGetComponent<ObjectInfoComponent>().tag;
    }
    return ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).tag;
}

void GameObject::SetTag(std::string tag) {
    if (entityID == 0) {
        TryGetComponent<ObjectInfoComponent>().tag = tag;
    } else {
        ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).tag = tag;
    }
}

bool GameObject::IsActive()const {
    if (entityID == 0) {
        return TryGetComponent<ObjectInfoComponent>().isActive;
    }
    return ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).isActive;
}

void GameObject::SetActive(bool active) {
    if (entityID == 0) {
        TryGetComponent<ObjectInfoComponent>().isActive = active;
    } else {
        ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).isActive = active;
    }
}

int GameObject::GetLayer() const{
    if (entityID == 0) {
        return TryGetComponent<ObjectInfoComponent>().layer;
    }
    return ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).layer;
}

void GameObject::SetLayer(int layer) {
    if (entityID == 0) {
        TryGetComponent<ObjectInfoComponent>().layer = layer;
    } else {
        ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).layer = layer;
    }
}

GameObject &GameObject::GetParent() {
    return *this;
}

uint32_t GameObject::GetEntityID()const {
    return entityID;
}

void GameObject::SetEntityID(uint32_t id) {
    entityID = id;
}

std::vector<std::unique_ptr<IComponent>> &GameObject::GetAllComponents() {
    return components;
}





