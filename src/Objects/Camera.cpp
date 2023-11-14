//
// Created by jesse on 31/10/2023.
//

#include "Objects/Camera.hpp"


Camera::Camera() : GameObject() {
    AddComponent(std::make_unique<CameraComponent>());
    SetBackgroundColor(Color(0, 0, 0, 255));
    SetSize(Vector2(800, 600));
}

Color Camera::GetBackgroundColor() const {
    if (entityID == 0) {
        return TryGetComponent<CameraComponent>()->backgroundColor;
    }
    return ComponentStore::GetInstance().tryGetComponent<CameraComponent>(entityID).backgroundColor;
}

void Camera::SetBackgroundColor(const Color color) {
    if (entityID == 0) {
        TryGetComponent<CameraComponent>()->backgroundColor = color;
    } else
        ComponentStore::GetInstance().tryGetComponent<CameraComponent>(entityID).backgroundColor = color;
}

Vector2 Camera::GetSize() const {
    if (entityID == 0){
        return TryGetComponent<CameraComponent>()->size;
    }
    return ComponentStore::GetInstance().tryGetComponent<CameraComponent>(entityID).size;
}

void Camera::SetSize(const Vector2 size) {
    if (entityID == 0) {
        TryGetComponent<CameraComponent>()->size = size;
    } else
        ComponentStore::GetInstance().tryGetComponent<CameraComponent>(entityID).size = size;
}