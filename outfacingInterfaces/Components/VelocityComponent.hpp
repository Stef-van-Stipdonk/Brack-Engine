//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_VELOCITYCOMPONENT_HPP
#define BRACK_ENGINE_VELOCITYCOMPONENT_HPP

#include "TransformComponent.hpp"

struct VelocityComponent : public TransformComponent {
    VelocityComponent() = default;

    ~VelocityComponent() = default;

    std::unique_ptr<Vector2> velocity;
};

#endif //BRACK_ENGINE_VELOCITYCOMPONENT_HPP
