//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ISYSTEM_HPP
#define BRACK_ENGINE_ISYSTEM_HPP

#include <algorithm>
#include "vector"
#include "../src/Logger.hpp"

class ISystem {
public:
    virtual ~ISystem() = default;

    // Wordt aangeroepen wanneer het system wordt geadd raan de gameloop, hoeft niet overschreven te worden
    virtual void Init() {}

    // Deze MOET iedere frame of gametick worden aangeroepen
    virtual void Update(float deltaTime) = 0;

    virtual const std::string GetName() const = 0;

    virtual void CleanUp() = 0;

    void AddDependency(ISystem* dependency) {
        if (std::find(outgoingEdges.begin(), outgoingEdges.end(), dependency) == outgoingEdges.end()) {
            outgoingEdges.push_back(dependency);
            Logger::Info("Dependency added for " + this->GetName() + ", " + this->GetName() + " now depends on " +
                         dependency->GetName());

            if(std::find(dependency->incomingEdges.begin(), dependency->incomingEdges.end(), this) == dependency->incomingEdges.end())
                dependency->incomingEdges.push_back(this);
        }
    }

    std::vector<ISystem*> outgoingEdges;
    std::vector<ISystem*> incomingEdges;


    const std::vector<ISystem*>& GetDependencies() const { return outgoingEdges; }

private:

};

#endif //BRACK_ENGINE_ISYSTEM_HPP
