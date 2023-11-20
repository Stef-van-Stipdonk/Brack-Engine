//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP

#include <memory>
#include <Helpers/CollisionType.hpp>
#include "CollisionComponent.hpp"


struct CircleCollisionComponent : public IComponent {

    explicit CircleCollisionComponent(float xRadius, float yRadius)
            : IComponent(), radius(new Vector2(xRadius, yRadius)) {}

    explicit CircleCollisionComponent(float radius) : CircleCollisionComponent(radius, radius) {}

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<CircleCollisionComponent>(*this);
    }

    ~CircleCollisionComponent() override {
        if (radius != nullptr)
            radius = nullptr;
    };

    CircleCollisionComponent(const CircleCollisionComponent &other) : IComponent(other) {
        if (other.radius != nullptr)
            radius = std::make_unique<Vector2>(*other.radius);
        collisionType = other.collisionType;
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::unique_ptr<Vector2> radius;
    CollisionType collisionType;
};

#endif //BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
