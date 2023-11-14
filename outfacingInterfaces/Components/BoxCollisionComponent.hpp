//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP

#include <memory>
#include "CollisionComponent.hpp"

struct BoxCollisionComponent : public CollisionComponent {
    explicit BoxCollisionComponent(Vector2 size) : CollisionComponent(), size(std::make_unique<Vector2>(size)) {}

    ~BoxCollisionComponent() override = default;


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<BoxCollisionComponent>(this);
    }

    std::unique_ptr<Vector2> size;
};

#endif //BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
