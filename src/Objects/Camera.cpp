//
// Created by jesse on 31/10/2023.
//

#include "Objects/Camera.hpp"


Camera::Camera() : GameObject() {
    AddComponent(new CameraComponent());
    SetBackgroundColor(Color(0, 0, 0, 255));
    SetSize(Vector2(800, 600));
}

void Camera::SetBackgroundColor(const Color color) {
    if (entityID == 0) {
        GetComponent<CameraComponent>()->backgroundColor = std::make_unique<Color>(color);
    } else
        ComponentStore::GetInstance().getComponent<CameraComponent>(
                entityID)->backgroundColor = std::make_unique<Color>(color);
}

void Camera::SetSize(const Vector2 size) {
    if (entityID == 0) {
        GetComponent<CameraComponent>()->size = std::make_unique<Vector2>(size);
    } else
        ComponentStore::GetInstance().getComponent<CameraComponent>(entityID)->size = std::make_unique<Vector2>(size);
}

void Camera::SetOnScreenPosition(const Vector2 position) {
    if (entityID == 0) {
        GetComponent<CameraComponent>()->onScreenPosition = std::make_unique<Vector2>(position);
    } else
        ComponentStore::GetInstance().getComponent<CameraComponent>(
                entityID)->onScreenPosition = std::make_unique<Vector2>(position);
}
