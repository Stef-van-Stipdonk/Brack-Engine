//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_MOVEMENTSYSTEM_HPP
#define BRACK_ENGINE_MOVEMENTSYSTEM_HPP


#include "ISystem.hpp"

class MovementSystem : public ISystem {
public:
    MovementSystem();

    ~MovementSystem() override;

    void Update(float deltaTime) override;
};


#endif //BRACK_ENGINE_MOVEMENTSYSTEM_HPP
