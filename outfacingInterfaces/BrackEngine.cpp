//
// Created by jesse on 02/11/2023.
//

#include "BrackEngine.hpp"
#include "../src/Systems/RenderingSystem.hpp"
#include "../src/Logger.hpp"
#include "../src/ConfigSingleton.hpp"

BrackEngine::BrackEngine(Config &&config) {
    ConfigSingleton::GetInstance().SetIsRunning(config.isRunning);
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
