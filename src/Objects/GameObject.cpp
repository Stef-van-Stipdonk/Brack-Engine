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

std::string GameObject::GetName() const {
    if (entityID == 0) {
        return tryGetComponent<ObjectInfoComponent>().name;
    }

    return ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).name;

}


void GameObject::SetName(std::string name) {
    if (entityID == 0) {
        tryGetComponent<ObjectInfoComponent>().name = name;
    } else {
        ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).name = name;
    }
}

std::string GameObject::GetTag() const {
    if (entityID == 0) {
        return tryGetComponent<ObjectInfoComponent>().tag;
    }
    return ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).tag;
}

void GameObject::SetTag(std::string tag) {
    if (entityID == 0) {
        tryGetComponent<ObjectInfoComponent>().tag = tag;
    } else {
        ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).tag = tag;
    }
}

bool GameObject::IsActive() const {
    if (entityID == 0) {
        return tryGetComponent<ObjectInfoComponent>().isActive;
    }
    return ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).isActive;
}

void GameObject::SetActive(bool active) {
    if (entityID == 0) {
        tryGetComponent<ObjectInfoComponent>().isActive = active;
    } else {
        ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).isActive = active;
    }
}

int GameObject::GetLayer() const {
    if (entityID == 0) {
        return tryGetComponent<ObjectInfoComponent>().layer;
    }
    return ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).layer;
}

void GameObject::SetLayer(int layer) {
    if (entityID == 0) {
        tryGetComponent<ObjectInfoComponent>().layer = layer;
    } else {
        ComponentStore::GetInstance().tryGetComponent<ObjectInfoComponent>(entityID).layer = layer;
    }
}

GameObject &GameObject::GetParent() {
    return *this;
}

entity GameObject::GetEntityID() const {
    return entityID;
}

void GameObject::SetEntityID(entity id) {
    entityID = id;
}

std::vector<std::unique_ptr<IComponent>> &GameObject::GetAllComponents() {
    return components;
}

void GameObject::setRotation(const float rotation) const {
    if (entityID == 0) {
        tryGetComponent<TransformComponent>().rotation = rotation;
    } else
        ComponentStore::GetInstance().tryGetComponent<TransformComponent>(
                entityID).rotation = rotation;
}





