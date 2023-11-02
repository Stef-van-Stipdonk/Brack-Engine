//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include "../../includes/SystemManager.hpp"
#include "Objects/Scene.hpp"

void SystemManager::AddSystem(ISystem *system) {
    systems.push_back(system);
    system->Init();
}

void SystemManager::UpdateSystems(float deltaTime) {
    for (auto system: systems) {
        system->Update(deltaTime);
    }
}

void SystemManager::Initialize(std::shared_ptr<EntityManager> newEntityManager) {
    entityManager = newEntityManager;
}
