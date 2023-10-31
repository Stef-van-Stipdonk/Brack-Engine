//
// Created by jesse on 31/10/2023.
//

#include "GameObject.hpp"

void GameObject::AddComponent(IComponent *component) {

}

GameObject GameObject::GetParent() {
    return GameObject();
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

template<typename T>
bool GameObject::HasComponent() {
    return false;
}

template<typename T>
T *GameObject::GetComponent() {
    return nullptr;
}
