//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP

#include <memory>
#include "../../src/Components/ComponentVisitor.hpp"
#include "CollisionComponent.hpp"

struct BoxCollisionComponent : public IComponent {
    explicit BoxCollisionComponent(float width, float height)
            : IComponent(), size(new Vector2(width, height)) {}

    explicit BoxCollisionComponent(float size) : BoxCollisionComponent(size, size) {}


    ~BoxCollisionComponent() override = default;


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<BoxCollisionComponent>(this);
    }

    std::unique_ptr<Vector2> size;
};

#endif //BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
