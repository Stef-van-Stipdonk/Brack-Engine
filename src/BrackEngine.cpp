//
// Created by jesse on 02/11/2023.
//

#include <Helpers/KeyMap.hpp>
#include <Helpers/MouseMap.hpp>
#include "BrackEngine.hpp"
#include "Systems/RenderingSystem.hpp"
#include "Logger.hpp"
#include "ConfigSingleton.hpp"
#include "Systems/InputSystem.hpp"

BrackEngine::BrackEngine(Config &&config) {
    ConfigSingleton::GetInstance().SetIsRunning(config.isRunning);
    SystemManager::GetInstance().AddSystem(new InputSystem());
    SystemManager::GetInstance().AddSystem(new RenderingSystem());
    lastTime = std::chrono::high_resolution_clock::now();
}

void BrackEngine::Run() {
    Logger::Debug("Updating systems");
    while (ConfigSingleton::GetInstance().IsRunning()){
        SystemManager::GetInstance().UpdateSystems(GetDeltaTime());
    }
    SystemManager::GetInstance().CleanUp();
}

float BrackEngine::GetDeltaTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime);
    lastTime = currentTime;

    float deltaTimeInSeconds = deltaTime.count();
    return deltaTimeInSeconds;
}

SceneManager &BrackEngine::GetSceneManager() const {
    return SceneManager::GetInstance();
}

InputManager &BrackEngine::GetInputManager() const {
    return InputManager::GetInstance();
}

ComponentStore &BrackEngine::GetComponentStore() const {
    return ComponentStore::GetInstance();
}

EntityManager &BrackEngine::GetEntityManager() const {
    return EntityManager::GetInstance();
}

ReplayManager &BrackEngine::GetReplayManager() const {
    return ReplayManager::GetInstance();
}

SystemManager &BrackEngine::GetSystemManager() const {
    return SystemManager::GetInstance();
}