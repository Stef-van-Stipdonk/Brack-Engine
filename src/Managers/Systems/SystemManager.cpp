//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include <stdexcept>
#include "../../includes/SystemManager.hpp"
#include "Objects/Scene.hpp"
#include "../../Logger.hpp"

SystemManager SystemManager::instance;

void SystemManager::AddSystem(ISystem* system) {
    systems.push_back(system);
    SortSystems();
}

void SystemManager::UpdateSystems(float deltaTime) {
    for (auto system: systems) {
        system->Update(deltaTime);
    }
}

SystemManager &SystemManager::GetInstance() {
    return instance;
}

void SystemManager::SortSystems() {
    std::vector<ISystem *> sortedList;
    std::vector<ISystem *> nodesWithoutIncomingEdges;

    for (auto system : systems) {
        if(system->incomingEdges.empty())
            nodesWithoutIncomingEdges.push_back(system);
    }

//    nodesWithoutIncomingEdges.

}

void SystemManager::CleanUp() {
    std::cout << "Finishing systems" << std::endl;
    for (auto system: systems) {
        system->CleanUp();
    }
}
