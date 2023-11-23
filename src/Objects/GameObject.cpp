//
// Created by jesse on 31/10/2023.
//

#include <Components/TransformComponent.hpp>
#include <Components/ObjectInfoComponent.hpp>
#include <Components/ParentComponent.hpp>
#include <Components/ChildComponent.hpp>
#include "Objects/GameObject.hpp"
#include <algorithm>
#include <utility>

GameObject::GameObject() {
    addComponent(std::make_unique<TransformComponent>());
    addComponent(std::make_unique<ObjectInfoComponent>());
}

std::vector<GameObject> GameObject::getChildren() const {
    try {
        auto &childComponent = tryGetComponent<ChildComponent>();
        std::vector<GameObject> children;
        for (auto &childId: childComponent.children) {
            auto child = GameObject();
            child.setEntityId(childId);
            children.push_back(child);
        }
    } catch (std::runtime_error &e) {
        return {};
    }
}

std::string GameObject::getName() const {
    return tryGetComponent<ObjectInfoComponent>().name;
}


void GameObject::setName(std::string name) const {
    tryGetComponent<ObjectInfoComponent>().name = std::move(name);
}

std::string GameObject::getTag() const {
    return tryGetComponent<ObjectInfoComponent>().tag;
}

void GameObject::setTag(std::string name) const {
    tryGetComponent<ObjectInfoComponent>().tag = std::move(name);
}

bool GameObject::isActive() const {
    return tryGetComponent<ObjectInfoComponent>().isActive;
}

void GameObject::setActive(bool active) const {
    tryGetComponent<ObjectInfoComponent>().isActive = active;
}


int GameObject::getLayer() const {
    return tryGetComponent<ObjectInfoComponent>().layer;
}

void GameObject::setLayer(int layer) const {
    tryGetComponent<ObjectInfoComponent>().layer = layer;
}

GameObject &GameObject::getParent() {
    return *this;
}

entity GameObject::getEntityId() const {
    return entityID;
}

void GameObject::setEntityId(entity id) {
    entityID = id;
}

std::vector<std::unique_ptr<IComponent>> &GameObject::getAllComponents() {
    return components;
}

void GameObject::addChild(GameObject &child) {
    try {
        auto &childComponent = ComponentStore::GetInstance().tryGetComponent<ChildComponent>(entityID);
        childComponent.children.push_back(child.getEntityId());
    } catch (std::runtime_error &e) {
        addComponent(std::make_unique<ChildComponent>());
        auto &childComponent = ComponentStore::GetInstance().tryGetComponent<ChildComponent>(entityID);
        childComponent.children.push_back(child.getEntityId());
    }

    try {
        auto &parentComponent = ComponentStore::GetInstance().tryGetComponent<ParentComponent>(child.getEntityId());
        parentComponent.parentId = entityID;
    } catch (std::runtime_error &e) {
        child.addComponent(ParentComponent());
        auto &parentComponent = ComponentStore::GetInstance().tryGetComponent<ParentComponent>(child.getEntityId());
        parentComponent.parentId = entityID;
    }
}

void GameObject::removeChild(GameObject &child) {
    try {
        auto &childComponent = tryGetComponent<ChildComponent>();
        auto it = std::find(childComponent.children.begin(), childComponent.children.end(),
                            child.getEntityId());
        if (it != childComponent.children.end()) {
            childComponent.children.erase(it);
            if (childComponent.children.empty()) {
                removeComponent<ChildComponent>();
            }
        }

        child.removeComponent<ParentComponent>();
    } catch (std::runtime_error &e) {
        // Do nothing
    }

}





