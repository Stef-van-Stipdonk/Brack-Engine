//
// Created by jesse on 02/11/2023.
//

#include <Helpers/KeyMap.hpp>
#include <Helpers/MouseMap.hpp>
#include "EngineManagers/InputManager.hpp"
#include "../Logger.hpp"

InputManager InputManager::instance;

void InputManager::SetKeyPressed(const int key) {
    if (keyInputs.find(key)->second == None || keyInputs.find(key)->second == Released) {
        keyInputs.find(key)->second = Clicked;
    }
}

void InputManager::SetKeyReleased(const int key) {
    keyInputs.find(key)->second = Released;
}

bool InputManager::IsKeyPressed(const int key) const {
    return keyInputs.find(key)->second == Pressed;
}

bool InputManager::IsKeyClicked(const int key) const {
    return keyInputs.find(key)->second == Clicked;
}

bool InputManager::IsKeyReleased(const int key) const {
    return keyInputs.find(key)->second == Released;
}

void InputManager::SetMousePressed(const int key) {
    mouseInputs.find(key)->second = Clicked;
}

void InputManager::SetMouseReleased(const int key) {
    mouseInputs.find(key)->second = Released;
}

bool InputManager::IsMousePressed(const int key) const {
    return mouseInputs.find(key)->second == Pressed;
}

bool InputManager::IsMouseClicked(const int key) const {
    return mouseInputs.find(key)->second == Clicked;
}

bool InputManager::IsMouseReleased(const int key) const {
    return mouseInputs.find(key)->second == Released;
}

void InputManager::SetKeyInputs(std::map<int, InputState> &inputs) {
    keyInputs = inputs;
}

void InputManager::SetMouseInputs(std::map<int, InputState> &inputs) {
    for (const auto &input: inputs) {
        auto it = mouseInputs.find(input.first);
        if (it != mouseInputs.end()) {
            // Update only if the key exists in mouseInputs
            it->second = input.second;
        }
    }
}

void InputManager::SetMousePosition(const Vector2 &position) {
    mousePosition.reset();
    mousePosition = std::make_unique<Vector2>(position);
}

std::map<int, InputState> InputManager::getActiveKeyInputs() {
    std::map<int, InputState> activeKeyInputs;
    for (const auto &item: keyInputs) {
        if (item.second != None) {
            activeKeyInputs[item.first] = item.second;
        }
    }
    return activeKeyInputs;
}

std::map<int, InputState> InputManager::getMouseInputs() {
    std::map<int, InputState> activeMouseInputs;
    for (const auto &item: mouseInputs) {
        if (item.second != None) {
            activeMouseInputs[item.first] = item.second;
        }
    }
    return activeMouseInputs;
}


std::unique_ptr<Vector2> &InputManager::getMousePositions() {
    return mousePosition;
}

Vector2 &InputManager::getMousePosition() const {
    return *mousePosition;
}

InputManager &InputManager::GetInstance() {
    return instance;
}

InputManager::InputManager() {
    mousePosition = std::make_unique<Vector2>(0, 0);
    mouseInputs.emplace(LEFT_MOUSE, None);
    mouseInputs.emplace(MIDDLE_MOUSE, None);
    mouseInputs.emplace(RIGHT_MOUSE, None);

    for (KeyMap key: {KeyMap_List}) {
        keyInputs.emplace(key, None);
    }
}

void InputManager::UpdateEvents() {

    for (auto &item: keyInputs) {
        if (item.second == Clicked) {
            item.second = Pressed;
        } else if (item.second == Released) {
            item.second = None;
        }
    }

    for (auto &item: mouseInputs) {
        if (item.second == Clicked) {
            item.second = Pressed;
        } else if (item.second == Released) {
            item.second = None;
        }
    }
}
