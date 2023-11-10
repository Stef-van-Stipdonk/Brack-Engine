//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP

#include <memory>
#include "CollisionComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct CircleCollisionComponent : public CollisionComponent {

    explicit CircleCollisionComponent() : CollisionComponent() {}

    ~CircleCollisionComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<CircleCollisionComponent>(this);
    }

    std::unique_ptr<Vector2> radius;
};

#endif //BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
