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

std::string ConfigSingleton::GetWindowTitle() const {
    return windowTitle;
}

Vector2 ConfigSingleton::GetWindowSize() const {
    return windowSize;
}

bool ConfigSingleton::IsFullscreen() const {
    return fullscreen;
}

std::string ConfigSingleton::GetBaseAssetPath() const {
    return BaseAssetPath;
}

void ConfigSingleton::SetConfig(Config config) {
    isRunning = config.isRunning;
    windowTitle = config.windowTitle;
    windowSize = config.windowSize;
    fullscreen = config.fullscreen;
    BaseAssetPath = config.BaseAssetPath;
    showFPS = config.showFPS;
}

bool ConfigSingleton::ShowFPS() const {
    return showFPS;
}
