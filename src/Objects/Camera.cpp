//
// Created by jesse on 31/10/2023.
//

#include "Objects/Camera.hpp"


Camera::Camera() : GameObject() {
    AddComponent(new CameraComponent());
    SetBackgroundColor(Color(0, 0, 0, 255));
    SetSize(Vector2(800, 600));
}

Color Camera::GetBackgroundColor() const {
    if (entityID == 0) {
        return GetComponent<CameraComponent>()->backgroundColor;
    }
    return ComponentStore::GetInstance().getComponent<CameraComponent>(entityID)->backgroundColor;
}

void Camera::SetBackgroundColor(const Color color) {
    if (entityID == 0) {
        GetComponent<CameraComponent>()->backgroundColor = color;
    } else
    ComponentStore::GetInstance().getComponent<CameraComponent>(entityID)->backgroundColor = color;
}

Vector2 Camera::GetSize() const {
    if (entityID == 0){
        return GetComponent<CameraComponent>()->size;
    }
    return ComponentStore::GetInstance().getComponent<CameraComponent>(entityID)->size;
}

void Camera::SetSize(const Vector2 size) {
    if (entityID == 0) {
        GetComponent<CameraComponent>()->size = size;
    } else
    ComponentStore::GetInstance().getComponent<CameraComponent>(entityID)->size = size;
}