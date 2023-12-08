//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_COLLISIONSYSTEM_HPP
#define BRACK_ENGINE_COLLISIONSYSTEM_HPP


#include "ISystem.hpp"

class CollisionSystem : public ISystem {
public:
    CollisionSystem();

    ~CollisionSystem() override;

    const std::string getName() const override;

    void cleanUp() override;
    void clearCache() override;

    void update(milliseconds deltaTime) override;
};


#endif //BRACK_ENGINE_COLLISIONSYSTEM_HPP
