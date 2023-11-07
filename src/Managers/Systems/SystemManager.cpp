//
// Created by Stef van Stipdonk on 29/10/2023.
//

#include <stdexcept>
#include "../../includes/SystemManager.hpp"
#include "Objects/Scene.hpp"
#include "../../Logger.hpp"

SystemManager SystemManager::instance;

void SystemManager::AddSystems(std::vector<ISystem*> systems) {
    for (auto system : systems) {
        this->systems.push_back(system);
        Logger::Info("Added system " + system->GetName());
    }
    SortSystems();
}


void SystemManager::AddSystem(ISystem* system) {
    systems.push_back(system);
    Logger::Info("Added system " + system->GetName());
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
    std::vector<ISystem*> sortedList;
    std::vector<ISystem*> nodesWithoutIncomingEdges;
    std::unordered_map<ISystem*, std::vector<ISystem*>> edgeCopy;

    // Backup the original incoming edges and initialize a copy for sorting
    for (auto system : systems) {
        edgeCopy[system] = system->incomingEdges;
        if (system->incomingEdges.empty()) {
            nodesWithoutIncomingEdges.push_back(system);
        }
    }

    while (!nodesWithoutIncomingEdges.empty()) {
        auto node = nodesWithoutIncomingEdges.back();
        nodesWithoutIncomingEdges.pop_back();
        sortedList.push_back(node);

        auto outgoingEdges = node->outgoingEdges;
        for (auto dependency : outgoingEdges) {
            auto& depIncomingEdgesCopy = edgeCopy[dependency];
            depIncomingEdgesCopy.erase(
                    std::remove(depIncomingEdgesCopy.begin(), depIncomingEdgesCopy.end(), node),
                    depIncomingEdgesCopy.end());

            if (depIncomingEdgesCopy.empty()) {
                nodesWithoutIncomingEdges.push_back(dependency);
            }
        }
    }

    for (auto& pair : edgeCopy) {
        if (!pair.second.empty()) {
            std::string systemName = pair.first->GetName(); // Assuming GetName is valid
            int edgeCount = pair.second.size();
            std::string incomingEdgeNames;
            for (auto* incomingEdgeSystem : pair.second) {
                if(incomingEdgeSystem) {
                    incomingEdgeNames += incomingEdgeSystem->GetName() + " ";
                } else {
                    incomingEdgeNames += "UnknownSystem ";
                }
            }

            Logger::Error(std::string("Graph has a cycle. System '") += systemName +=
                                     std::string("' has ") += std::to_string(edgeCount) +
                                     " incoming edge(s) from: " += incomingEdgeNames);

            throw std::runtime_error("Graph has a cycle, look at the log for more information."
                                     "The program will now exit.");
        }
    }



    std::reverse(sortedList.begin(), sortedList.end());

    systems = sortedList;
}





void SystemManager::CleanUp() {
    std::cout << "Finishing systems" << std::endl;
    for (auto system: systems) {
        system->CleanUp();
    }
}
