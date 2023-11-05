//
// Created by jesse on 31/10/2023.
//

#include "Camera.hpp"

Color Camera::GetBackgroundColor() const {
    return Color();
}

void Camera::SetBackgroundColor(const Color color) {
    backgroundColor = color;
}

Vector2 Camera::GetSize() const {
    return Vector2();
}

void Camera::SetSize(const Vector2 size) {

}

Camera::Camera() : GameObject() {
    size = Vector2(800, 600);
    backgroundColor = Color(0, 0, 0, 255);
}
