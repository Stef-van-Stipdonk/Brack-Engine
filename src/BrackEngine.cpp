//
// Created by jesse on 02/11/2023.
//

#include "BrackEngine.hpp"
#include "Systems/RenderingSystem.hpp"
#include "Logger.hpp"
#include "ConfigSingleton.hpp"

BrackEngine::BrackEngine(Config &&config) {
    ConfigSingleton::GetInstance().SetIsRunning(config.isRunning);
    auto renderingSystem = new RenderingSystem();
    auto audioSystem = new AudioSystem();
    auto physicsSystem = new PhysicsSystem();
    auto replaySystem = new ReplaySystem();
    renderingSystem->AddDependency(audioSystem);
    renderingSystem->AddDependency(replaySystem);
    physicsSystem->AddDependency(renderingSystem);
    physicsSystem->AddDependency(audioSystem);
    audioSystem->AddDependency(physicsSystem);
    audioSystem->AddDependency(replaySystem);
    SystemManager::GetInstance().AddSystem(renderingSystem);
    SystemManager::GetInstance().AddSystem(audioSystem);
    SystemManager::GetInstance().AddSystem(physicsSystem);
    SystemManager::GetInstance().AddSystem(replaySystem);
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
