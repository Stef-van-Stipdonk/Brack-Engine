//
// Created by jesse on 31/10/2023.
//

#include "InputSystem.hpp"
#include "EngineManagers/InputManager.hpp"

InputSystem::InputSystem() {
    inputWrapper = std::make_unique<InputWrapper>();
}

InputSystem::~InputSystem() {
    inputWrapper.reset();
}

void InputSystem::update(milliseconds deltaTime) {
    InputManager::getInstance().UpdateEvents();
    if (inputWrapper != nullptr)
        inputWrapper->HandleEvents();
}

const std::string InputSystem::getName() const {
    return "InputSystem";
}

void InputSystem::cleanUp() {
}

void InputSystem::clearCache() {
}

InputSystem::InputSystem(const InputSystem &other) {
    inputWrapper = std::make_unique<InputWrapper>(*other.inputWrapper);
}

void InputSystem::setInputWrapper(std::unique_ptr<InputWrapper> wrapper) {
    inputWrapper = std::move(wrapper);
}

