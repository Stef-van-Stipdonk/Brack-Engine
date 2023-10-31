//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PHYSICSSYSTEM_HPP
#define BRACK_ENGINE_PHYSICSSYSTEM_HPP


#include "ISystem.hpp"

class PhysicsSystem : public ISystem {
public:
    PhysicsSystem();

    ~PhysicsSystem() override;

    void Update(float deltaTime) override;
};


#endif //BRACK_ENGINE_PHYSICSSYSTEM_HPP
