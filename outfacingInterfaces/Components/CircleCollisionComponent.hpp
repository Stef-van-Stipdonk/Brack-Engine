//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP

#include "CollisionComponent.hpp"

class CircleCollisionComponent : public CollisionComponent {
public:
    CircleCollisionComponent() = default;

    ~CircleCollisionComponent() override = default;

    Vector2 radius;
};

#endif //BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
