//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_SYSTEMMANAGER_HPP
#define BRACK_ENGINE_SYSTEMMANAGER_HPP

// TODO kijk naar deze improvements voor system exectutie order (Het zijn er 2) kijk welke hier het beste is:
// 1. Topological Sorting:
// Treat your systems as nodes and their dependencies as directed edges. Use topological sorting to determine an execution order that respects the dependencies.
// 1.1. Create a dependency graph where each system is a node.
// 1.2. Directed edges represent dependencies.
// 1.3. Run a topological sort on the graph.
// 1.4. The resulting order from the sort is the correct execution order.
// This approach ensures there's no circular dependencies and that systems are executed in an order that respects the dependency relationships.

// 2. Dependency Matrix:
// Use a matrix (or table) to represent dependencies between systems.
// 2.1 Rows and columns both represent systems.
// 2.2 Matrix entry (i, j) indicates whether system i depends on system j.
// Iterate and resolve dependencies based on the matrix to determine the execution order.

#include <vector>
#include <memory>
#include "../../outfacingInterfaces/ISystem.hpp"
#include "EntityManager.hpp"

class SystemManager {
public:
    static SystemManager &GetInstance();

    ~SystemManager() = default;

    SystemManager(const SystemManager &) = delete;

    SystemManager &operator=(const SystemManager &) = delete;

    SystemManager(SystemManager &&) = delete;

    SystemManager &operator=(SystemManager &&) = delete;

    /// <summary>
    /// Finds a system by type
    /// </summary>
    template<typename T>
    std::shared_ptr<T> FindSystem() {
        for (auto& system : systems) {
            auto castedSystem = std::dynamic_pointer_cast<T>(system);
            if (castedSystem) {
                return castedSystem;
            }
        }

        Logger::Warning(std::string("System not found: ") + typeid(T).name());
        return nullptr;
    }


    template<typename T>
    void RemoveSystem() {
        auto it = std::remove_if(systems.begin(), systems.end(),
                                 [](const std::shared_ptr<ISystem>& system) {
                                     return std::dynamic_pointer_cast<T>(system) != nullptr;
                                 }
        );

        if (it != systems.end()) {
            systems.erase(it, systems.end());
        } else {
            Logger::Warning(std::string("System not found: ") + typeid(T).name());
        }
    }

    /// <summary>
    /// Adds a system to the system manager
    /// Should be used when you want to add a single system
    /// If adding multiple systems at once which are dependent on each other, use AddSystems
    /// </summary>
    /// <param name="system">The system to add</param>
    /// <param name="printGraph">Whether or not to print the dependency graph after adding the system to see the state of the graph</param>
    void AddSystem(std::shared_ptr<ISystem> system, bool printGraph = false);

    /// <summary>
    /// Adds a list of systems to the system manager
    /// Should be used when you want to add multiple systems at once
    /// </summary>
    /// <param name="systems">The list of systems to add</param>
    /// <param name="printGraph">Whether or not to print the dependency graph after adding the system to see the state of the graph</param>
    void AddSystems(std::vector<std::shared_ptr<ISystem>> newSystems, bool printGraph = false);

    void UpdateSystems(float deltaTime);
    void CleanUp();

    /// <summary>
    /// Prints the dependency graph to the console, is not logged to file(not compiled in release mode)
    /// </summary>
    void PrintDependencyGraph() const;

    void SortSystems();
private:

    SystemManager() = default;

    static SystemManager instance;
    std::vector<std::shared_ptr<ISystem>> systems;
};


#endif //BRACK_ENGINE_SYSTEMMANAGER_HPP
