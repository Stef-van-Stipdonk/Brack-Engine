//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_SYSTEMMANAGER_HPP
#define BRACK_ENGINE_SYSTEMMANAGER_HPP

#include <vector>
#include <memory>
#include "../../outfacingInterfaces/ISystem.hpp"
#include "EntityManager.hpp"

class SystemManager {
public:
    static SystemManager &getInstance();

    ~SystemManager() = default;

    SystemManager(const SystemManager &) = delete;

    SystemManager &operator=(const SystemManager &) = delete;

    SystemManager(SystemManager &&) = delete;

    SystemManager &operator=(SystemManager &&) = delete;

    /// <summary>
    /// Finds a system by type and returns a weak pointer to it
    /// </summary>
    /// <typeparam name="T">The type of system to find</typeparam>
    /// <returns>A weak pointer to the system</returns>
    template<typename T>
    std::weak_ptr<T> GetSystem() {
        auto systemIt = std::find_if(systems.begin(), systems.end(),
                                     [](const std::shared_ptr<ISystem> &system) {
                                         return std::dynamic_pointer_cast<T>(system) != nullptr;
                                     });

        if (systemIt != systems.end()) {
            return std::dynamic_pointer_cast<T>(*systemIt);
        } else {
            Logger::Warning(std::string("System not found: ") + typeid(T).name());
            return std::weak_ptr<T>();
        }
    }


    template<typename T>
    typename std::enable_if<std::is_base_of<ISystem, T>::value>::type
    RemoveSystem() {
        // Find the system to remove
        auto systemToRemoveIt = std::find_if(systems.begin(), systems.end(),
                                             [](const std::shared_ptr<ISystem> &system) {
                                                 return std::dynamic_pointer_cast<T>(system) != nullptr;
                                             });

        if (systemToRemoveIt != systems.end()) {
            auto systemToRemove = *systemToRemoveIt;

            // Remove this system as a dependency from other systems
            for (auto &system: systems) {
                system->removeDependency(systemToRemove);
            }

            // Now remove the system itself
            systems.erase(systemToRemoveIt);
            SortSystems();
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

    void UpdateSystems(milliseconds deltaTime);

    void CleanUp();

    /// <summary>
    /// Prints the dependency graph to the console, is not logged to file(not compiled in release mode)
    /// </summary>
    void PrintDependencyGraph() const;

    void SortSystems();

    void clearSystemsCache();

    std::vector<std::shared_ptr<ISystem>> getCopyOfSystems();

    void clearSystems();

private:

    SystemManager() = default;

    static SystemManager instance;
    std::vector<std::shared_ptr<ISystem>> systems;

};


#endif //BRACK_ENGINE_SYSTEMMANAGER_HPP
