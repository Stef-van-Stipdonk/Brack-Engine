//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_COLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_COLLISIONCOMPONENT_HPP

#include "TransformComponent.hpp"

struct CollisionComponent : public TransformComponent {
    explicit CollisionComponent(uint32_t entityId) : TransformComponent(entityId) {}

    virtual ~CollisionComponent() = default;
};

#endif //BRACK_ENGINE_COLLISIONCOMPONENT_HPP
