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

    void update(float deltaTime) override;

    const std::string GetName() const override;

    void CleanUp() override;

    const std::string getName() const override;


private:
    std::unique_ptr<PhysicsWrapper> physicsWrapper;

    void handleCircles();

    void handleBoxes();
};


#endif //BRACK_ENGINE_PHYSICSSYSTEM_HPP
