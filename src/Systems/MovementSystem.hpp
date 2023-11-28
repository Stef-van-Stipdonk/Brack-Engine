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

    void update(int deltaTime) override;

    const std::string getName() const override;

    void cleanUp() override;
};


#endif //BRACK_ENGINE_MOVEMENTSYSTEM_HPP
