//
// Created by jesse on 31/10/2023.
//

#include "Objects/Camera.hpp"

Color Camera::GetBackgroundColor() const {
    return backgroundColor;
}

void Camera::SetBackgroundColor(const Color color) {
    backgroundColor = color;
}

Vector2 Camera::GetSize() const {
    return size;
}

void Camera::SetSize(const Vector2 size) {

}

Camera::Camera() : GameObject() {
    size = Vector2(800, 600);
    backgroundColor = Color(0, 0, 0, 255);
}

CameraComponent *Camera::GetCameraComponent() {
    return cameraComponent;
}

void Camera::SetCameraComponent(CameraComponent *cameraComponent) {
    this->cameraComponent = cameraComponent;
}
