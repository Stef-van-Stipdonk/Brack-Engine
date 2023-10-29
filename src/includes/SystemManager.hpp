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
#include "../../outfacingInterfaces/ISystem.hpp"

class SystemManager {
private:
    std::vector<ISystem*> systems;

public:
    void AddSystem(ISystem* system);

    void UpdateSystems(float deltaTime);
};



#endif //BRACK_ENGINE_SYSTEMMANAGER_HPP
