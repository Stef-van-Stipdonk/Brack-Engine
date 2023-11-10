//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_VELOCITYCOMPONENT_HPP
#define BRACK_ENGINE_VELOCITYCOMPONENT_HPP

#include "TransformComponent.hpp"

struct VelocityComponent : public TransformComponent {
    explicit VelocityComponent() : TransformComponent() {}

    ~VelocityComponent() = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<VelocityComponent>(this);
    }

    Vector2 velocity;
};

#endif //BRACK_ENGINE_VELOCITYCOMPONENT_HPP
