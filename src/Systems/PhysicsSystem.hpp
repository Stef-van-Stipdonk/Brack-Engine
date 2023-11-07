//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PHYSICSSYSTEM_HPP
#define BRACK_ENGINE_PHYSICSSYSTEM_HPP


#include <memory>
#include "ISystem.hpp"
#include "../Wrappers/PhysicsWrapper.hpp"

class PhysicsSystem : public ISystem {
public:
    PhysicsSystem();

    ~PhysicsSystem() override;

    void Update(float deltaTime) override;

    std::string GetName() override;
    void CleanUp() override;

private:
    std::unique_ptr <PhysicsWrapper> physicsWrapper;
};


#endif //BRACK_ENGINE_PHYSICSSYSTEM_HPP
