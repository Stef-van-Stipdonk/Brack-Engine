//
// Created by jesse on 31/10/2023.
//

#include "Objects/Camera.hpp"
#include "../ConfigSingleton.hpp"

#include <memory>


Camera::Camera() : GameObject() {
    AddComponent(std::make_unique<CameraComponent>());
    SetBackgroundColor(Color(0, 0, 0, 255));
    auto size = ConfigSingleton::GetInstance().GetWindowSize();
    SetSize(size);
}

void Camera::SetBackgroundColor(const Color& color) {
    if (entityID == 0) {
        GetComponent<CameraComponent>()->backgroundColor = std::make_unique<Color>(color);
    } else
    ComponentStore::GetInstance().getComponent<CameraComponent>(entityID)->backgroundColor = std::make_unique<Color>(color);
}

void Camera::SetSize(const Vector2& size) {
    if (entityID == 0) {
        GetComponent<CameraComponent>()->size = std::make_unique<Vector2>(size);
    } else
    ComponentStore::GetInstance().getComponent<CameraComponent>(entityID)->size = std::make_unique<Vector2>(size);
}