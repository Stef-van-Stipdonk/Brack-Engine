//
// Created by jesse on 02/11/2023.
//

#include "BrackEngine.hpp"
#include "../src/Systems/RenderingSystem.hpp"
#include "../src/Logger.hpp"
#include "../src/ConfigSingleton.hpp"


void BrackEngine::Update() {
//    Logger::Debug("Updating systems");
    while (ConfigSingleton::GetInstance().IsRunning()){
        SystemManager::GetInstance().UpdateSystems(GetDeltaTime());
    }
}

BrackEngine::BrackEngine(Config &&config) {
    ConfigSingleton::GetInstance().SetIsRunning(config.isRunning);
    SystemManager::GetInstance().AddSystem(new RenderingSystem());
    lastTime = clock.now();
}

float BrackEngine::GetDeltaTime() {
    auto currentTime = clock.now();
    std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime);
    lastTime = currentTime;

    float deltaTimeInSeconds = deltaTime.count();
    return deltaTimeInSeconds;
}
