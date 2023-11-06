//
// Created by jesse on 02/11/2023.
//

#include "BrackEngine.hpp"
#include "../src/Systems/RenderingSystem.hpp"
#include "../src/Logger.hpp"
#include "../src/ConfigSingleton.hpp"


void BrackEngine::Update() {
    Logger::Debug("Updating systems");
    while (ConfigSingleton::GetInstance().IsRunning()){
        SystemManager::GetInstance().UpdateSystems();
    }
}

BrackEngine::BrackEngine(Config &&config) {
    ConfigSingleton::GetInstance().SetIsRunning(config.isRunning);
    SystemManager::GetInstance().AddSystem(new RenderingSystem());
}
