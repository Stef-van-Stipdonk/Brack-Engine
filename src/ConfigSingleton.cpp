//
// Created by jesse on 06/11/2023.
//

#include "ConfigSingleton.hpp"

ConfigSingleton ConfigSingleton::instance;

ConfigSingleton &ConfigSingleton::GetInstance() {
    return instance;
}

bool ConfigSingleton::IsRunning() const {
    return isRunning;
}

void ConfigSingleton::ToggleIsRunning() {
    isRunning = !isRunning;
}

void ConfigSingleton::SetIsRunning(bool isRunning) {
    ConfigSingleton::isRunning = isRunning;
}
