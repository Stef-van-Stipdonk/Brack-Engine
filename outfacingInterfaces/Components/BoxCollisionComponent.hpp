//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP

#include <memory>
#include "CollisionComponent.hpp"

struct BoxCollisionComponent : public CollisionComponent {
    explicit BoxCollisionComponent(uint32_t entityId) : CollisionComponent(entityId) {}

    ~BoxCollisionComponent() override = default;

    std::unique_ptr<Vector2> size;
};

#endif //BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
