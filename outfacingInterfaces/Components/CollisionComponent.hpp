//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_COLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_COLLISIONCOMPONENT_HPP

#include "TransformComponent.hpp"

class CollisionComponent : public TransformComponent {
public:
    virtual ~CollisionComponent() = default;
};

#endif //BRACK_ENGINE_COLLISIONCOMPONENT_HPP
