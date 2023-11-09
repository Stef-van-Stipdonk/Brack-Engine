//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ISYSTEM_HPP
#define BRACK_ENGINE_ISYSTEM_HPP

#include <algorithm>
#include "vector"
#include "../src/Logger.hpp"

class ISystem : public std::enable_shared_from_this<ISystem> {
public:
    virtual ~ISystem() = default;
    virtual void Init() {}
    virtual void Update(float deltaTime) = 0;
    virtual const std::string GetName() const = 0;
    virtual void CleanUp() = 0;

    void AddDependency(std::shared_ptr<ISystem> dependency) {
        auto thisPtr = shared_from_this();

        bool dependencyExists = std::any_of(outgoingEdges.begin(), outgoingEdges.end(),
                                            [&dependency](const std::weak_ptr<ISystem>& weakPtr) {
                                                auto sharedPtr = weakPtr.lock();
                                                return sharedPtr == dependency;
                                            }
        );

        if (!dependencyExists) {
            outgoingEdges.push_back(dependency);
            Logger::Info("Dependency added for " + this->GetName() + ", " + this->GetName() + " now depends on " +
                         dependency->GetName());

            bool backLinkExists = std::any_of(dependency->incomingEdges.begin(), dependency->incomingEdges.end(),
                                              [thisPtr](const std::weak_ptr<ISystem>& weakPtr) {
                                                  auto sharedPtr = weakPtr.lock();
                                                  return sharedPtr == thisPtr;
                                              }
            );

            if (!backLinkExists) {
                dependency->incomingEdges.push_back(thisPtr);
            }
        }
    }


    std::vector<std::weak_ptr<ISystem>> outgoingEdges;
    std::vector<std::weak_ptr<ISystem>> incomingEdges;


    const std::vector<std::weak_ptr<ISystem>>& GetDependencies() const { return outgoingEdges; }

private:

};

#endif //BRACK_ENGINE_ISYSTEM_HPP
