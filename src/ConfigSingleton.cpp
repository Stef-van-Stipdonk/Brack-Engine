//
// Created by jesse on 06/11/2023.
//

#include "../outfacingInterfaces/ConfigSingleton.hpp"

#include <../outfacingInterfaces/EngineManagers/SceneManager.hpp>

#include "includes/EntityManager.hpp"


ConfigSingleton ConfigSingleton::instance;

ConfigSingleton &ConfigSingleton::getInstance() {
    return instance;
}

bool ConfigSingleton::isRunning() const {
    return isRunning_;
}

void ConfigSingleton::toggleIsRunning() {
    isRunning_ = !isRunning_;
}

void ConfigSingleton::setDeltaTimeMultiplier(float deltaTimeMultiplier) {
    ConfigSingleton::instance.deltaTimeMultiplier = deltaTimeMultiplier;
}

void ConfigSingleton::setIsRunning(bool isRunning) {
    ConfigSingleton::isRunning_ = isRunning;
}

std::string ConfigSingleton::getWindowTitle() const {
    return windowTitle;
}

Vector2 ConfigSingleton::getWindowSize() const {
    return windowSize;
}

Vector2 ConfigSingleton::getInitialWindowSize() const {
    return initialWindowSize;
}

bool ConfigSingleton::isFullscreen() const {
    return fullscreen;
}

int ConfigSingleton::getParticleLimit() const {
    return particleLimit;
}

std::string ConfigSingleton::getBaseAssetPath() const {
    return BaseAssetPath;
}

int ConfigSingleton::getAmountOfSoundEffectsChannels() const {
    return amountOfSoundEffectsChannels;
}

void ConfigSingleton::setConfig(Config config) {
    isRunning_ = config.isRunning;
    windowTitle = config.windowTitle;
    if (config.windowSize == Vector2(0, 0))
        windowSize = config.initialWindowSize;
    initialWindowSize = config.initialWindowSize;
    fullscreen = config.fullscreen;
    BaseAssetPath = config.BaseAssetPath;
    showFPS_ = config.showFPS;
    amountOfSoundEffectsChannels = config.amountOfSoundEffectsChannels;
    fpsLimit = config.fpsLimit;
    particleLimit = config.particleLimit;
    deltaTimeMultiplier = config.deltaTimeMultiplier;
    if (config.appLogoPath != "")
        appLogoPath = config.appLogoPath;
}

bool ConfigSingleton::showFps() const {
    return showFPS_;
}

void ConfigSingleton::toggleShowFps() {
    showFPS_ = !showFPS_;
    if (EntityManager::getInstance().entityExistsByTag("FPS")) {
        SceneManager::getInstance().getGameObjectByName("FPS").value()->setActive(showFPS_);
    }
}

void ConfigSingleton::setWindowSize(Vector2 size) {
    windowSize = size;
}

uint32_t ConfigSingleton::getFPSLimit() const {
    return fpsLimit;
}

void ConfigSingleton::setFPSLimit(uint32_t fpsLimit) {
    ConfigSingleton::fpsLimit = fpsLimit;
}

Vector2 ConfigSingleton::getWindowChangeFactor() const {
    return windowSize / initialWindowSize;
}

float ConfigSingleton::getAspectRatio() const {
    return initialWindowSize.getX() / initialWindowSize.getY();
}

void ConfigSingleton::toggleFullScreen() {
    fullscreen = !fullscreen;
}

std::string ConfigSingleton::getAppLogoPath() const {
    return appLogoPath;
}
