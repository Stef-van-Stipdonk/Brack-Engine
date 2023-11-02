//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include "../../includes/SystemManager.hpp"
#include "Objects/Scene.hpp"

SystemManager SystemManager::instance;

void SystemManager::AddSystem(ISystem *system) {
    systems.push_back(system);
    system->Init();
}

void SystemManager::UpdateSystems(float deltaTime) {
    for (auto system: systems) {
        system->Update(deltaTime);
    }
}

SystemManager &SystemManager::GetInstance() {
    return instance;
}
