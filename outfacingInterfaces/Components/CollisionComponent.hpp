//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_COLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_COLLISIONCOMPONENT_HPP

#include "TransformComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct CollisionComponent : public TransformComponent {
    explicit CollisionComponent() : TransformComponent() {}

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<CollisionComponent>(*this);
    }

    virtual ~CollisionComponent() = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    CollisionComponent(const CollisionComponent& other) : TransformComponent(other) {}
};

#endif //BRACK_ENGINE_COLLISIONCOMPONENT_HPP
