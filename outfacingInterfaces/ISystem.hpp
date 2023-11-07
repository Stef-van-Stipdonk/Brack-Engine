//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ISYSTEM_HPP
#define BRACK_ENGINE_ISYSTEM_HPP

#include <algorithm>
#include "vector"

class ISystem {
public:
    virtual ~ISystem() = default;

    // Wordt aangeroepen wanneer het system wordt geadd raan de gameloop, hoeft niet overschreven te worden
    virtual void Init() {}

    // Deze MOET iedere frame of gametick worden aangeroepen
    virtual void Update(float deltaTime) = 0;

    virtual void CleanUp() {}
    virtual std::string GetName() = 0;

    virtual void CleanUp() = 0;
    
    void AddDependency(ISystem* dependency) {
        if (std::find(dependencies.begin(), dependencies.end(), dependency) == dependencies.end()) {
            dependencies.push_back(dependency);
        }
    }

    const std::vector<ISystem*>& GetDependencies() const { return dependencies; }

private:
    std::vector<ISystem*> dependencies;
};

#endif //BRACK_ENGINE_ISYSTEM_HPP
