//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_COLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_COLLISIONCOMPONENT_HPP

#include "TransformComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct CollisionComponent : public TransformComponent {
    explicit CollisionComponent() : TransformComponent() {}

    virtual ~CollisionComponent() = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }
};

#endif //BRACK_ENGINE_COLLISIONCOMPONENT_HPP
