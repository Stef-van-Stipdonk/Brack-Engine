//
// Created by jesse on 31/10/2023.
//

#include "InputSystem.hpp"

InputSystem::InputSystem() {
    inputWrapper = std::make_unique<InputWrapper>();
}

InputSystem::~InputSystem() {
    inputWrapper.reset();
}

void InputSystem::Update(float deltaTime) {
    inputWrapper->HandleEvents();
}
