//
// Created by jesse on 31/10/2023.
//

#include <Components/TransformComponent.hpp>
#include <Components/ObjectInfoComponent.hpp>
#include "Objects/GameObject.hpp"

GameObject::GameObject() {
    TransformComponent *transFormComponent = new TransformComponent();
    ObjectInfoComponent *objectInfoComponent = new ObjectInfoComponent();
    AddComponent(transFormComponent);
    AddComponent(objectInfoComponent);
}

std::vector<GameObject> GameObject::GetChildren() {
    return std::vector<GameObject>();
}

std::string GameObject::GetName() {
    return std::string();
}


void GameObject::SetName(char *name) {

}

std::string GameObject::GetTag() {
    return std::string();
}

void GameObject::SetTag(char *tag) {

}

bool GameObject::IsActive() {
    return false;
}

void GameObject::SetActive(bool active) {

}

int GameObject::GetLayer() {
    return 0;
}

void GameObject::SetLayer(int layer) {

}

GameObject &GameObject::GetParent() {
    return *this;
}

uint32_t GameObject::GetEntityID() {
    return entityID;
}

void GameObject::SetEntityID(uint32_t id) {
    entityID = id;
}

std::vector<IComponent *> & GameObject::GetAllComponents() {
    return components;
}





