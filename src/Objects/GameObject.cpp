//
// Created by jesse on 31/10/2023.
//

#include <Components/TransformComponent.hpp>
#include <Components/ObjectInfoComponent.hpp>
#include "Objects/GameObject.hpp"

GameObject::GameObject() {
    auto *transformComponent = new TransformComponent();
    auto *objectInfoComponent = new ObjectInfoComponent();
    AddComponent(transformComponent);
    AddComponent(objectInfoComponent);
}

std::vector<GameObject> GameObject::GetChildren() {
    return std::vector<GameObject>();
}

std::string GameObject::GetName() const{
    if (entityID == 0) {
        return GetComponent<ObjectInfoComponent>()->name;
    }

    return ComponentStore::GetInstance().getComponent<ObjectInfoComponent>(entityID)->name;

}


void GameObject::SetName(char *name) {
    if (entityID == 0) {
        GetComponent<ObjectInfoComponent>()->name = name;
    } else {
        ComponentStore::GetInstance().getComponent<ObjectInfoComponent>(entityID)->name = name;
    }
}

std::string GameObject::GetTag() const{
    if (entityID == 0) {
        return GetComponent<ObjectInfoComponent>()->tag;
    }
    return ComponentStore::GetInstance().getComponent<ObjectInfoComponent>(entityID)->tag;
}

void GameObject::SetTag(char *tag) {
    if (entityID == 0) {
        GetComponent<ObjectInfoComponent>()->tag = tag;
    } else {
        ComponentStore::GetInstance().getComponent<ObjectInfoComponent>(entityID)->tag = tag;
    }
}

bool GameObject::IsActive()const {
    if (entityID == 0) {
        return GetComponent<ObjectInfoComponent>()->isActive;
    }
    return ComponentStore::GetInstance().getComponent<ObjectInfoComponent>(entityID)->isActive;
}

void GameObject::SetActive(bool active) {
    if (entityID == 0) {
        GetComponent<ObjectInfoComponent>()->isActive = active;
    } else {
        ComponentStore::GetInstance().getComponent<ObjectInfoComponent>(entityID)->isActive = active;
    }
}

int GameObject::GetLayer() const{
    if (entityID == 0) {
        return GetComponent<ObjectInfoComponent>()->layer;
    }
    return ComponentStore::GetInstance().getComponent<ObjectInfoComponent>(entityID)->layer;
}

void GameObject::SetLayer(int layer) {
    if (entityID == 0) {
        GetComponent<ObjectInfoComponent>()->layer = layer;
    } else {
        ComponentStore::GetInstance().getComponent<ObjectInfoComponent>(entityID)->layer = layer;
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

std::vector<IComponent *> &GameObject::GetAllComponents() {
    return components;
}





