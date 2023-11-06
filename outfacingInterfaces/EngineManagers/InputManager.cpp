//
// Created by jesse on 02/11/2023.
//

#include "InputManager.hpp"

InputManager InputManager::instance;

void InputManager::SetKeyPressed(const int key) {

}

void InputManager::SetKeyReleased(const int key) {

}

bool InputManager::IsKeyPressed(const int key) const {
    return false;
}

bool InputManager::IsKeyClicked(const int key) const {
    return false;
}

bool InputManager::IsKeyReleased(const int key) const {
    return false;
}

void InputManager::SetMousePressed(const int key) {

}

void InputManager::SetMouseReleased(const int key) {

}

bool InputManager::IsMousePressed(const int key) const {
    return false;
}

bool InputManager::IsMouseClicked(const int key) const {
    return false;
}

bool InputManager::IsMouseReleased(const int key) const {
    return false;
}

void InputManager::SetMousePosition(const Vector2 &position) {

}

Vector2 &InputManager::GetMousePosition() const {
    return *mousePosition;
}

InputManager &InputManager::GetInstance() {
    return instance;
}
