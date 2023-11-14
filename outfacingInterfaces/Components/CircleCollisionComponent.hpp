//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP

#include <memory>
#include "CollisionComponent.hpp"


struct CircleCollisionComponent : public CollisionComponent {

    explicit CircleCollisionComponent(float xRadius, float yRadius) : CollisionComponent(), radius(new Vector2(xRadius,yRadius)) {}
    explicit CircleCollisionComponent(float radius) : CircleCollisionComponent(radius,radius) {}

    ~CircleCollisionComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<CircleCollisionComponent>(this);
    }

    std::unique_ptr<Vector2> radius;
};

#endif //BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
