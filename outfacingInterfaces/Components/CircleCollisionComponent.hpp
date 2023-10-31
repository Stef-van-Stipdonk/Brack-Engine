//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP

#include <memory>
#include "CollisionComponent.hpp"

struct CircleCollisionComponent : public CollisionComponent {
    CircleCollisionComponent() = default;

    ~CircleCollisionComponent() override = default;

    std::unique_ptr<Vector2> radius;
};

#endif //BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
