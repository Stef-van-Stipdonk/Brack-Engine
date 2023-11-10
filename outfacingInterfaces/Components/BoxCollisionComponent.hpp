//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP

#include <memory>
#include "../../src/Components/ComponentVisitor.hpp"
#include "CollisionComponent.hpp"

struct BoxCollisionComponent : public CollisionComponent {
    explicit BoxCollisionComponent() : CollisionComponent() {}

    ~BoxCollisionComponent() override = default;


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<BoxCollisionComponent>(this);
    }

    std::unique_ptr<Vector2> size;
};

#endif //BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
