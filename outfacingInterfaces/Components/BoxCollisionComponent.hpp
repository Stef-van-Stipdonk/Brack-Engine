//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP

#include <memory>
#include <vector>
#include <Helpers/CollisionType.hpp>
#include "Archetypes/CollisionArchetype.hpp"
#include "Helpers/Vector2.hpp"


struct BoxCollisionComponent : public CollisionArchetype {
    explicit BoxCollisionComponent(Vector2 size) : CollisionArchetype(), size(std::make_unique<Vector2>(size)) {}


    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<BoxCollisionComponent>(*this);
    }

    ~BoxCollisionComponent() override {
        size = nullptr;
    };

    BoxCollisionComponent(const BoxCollisionComponent &other) : CollisionArchetype(other) {
        size = std::make_unique<Vector2>(*other.size);
        collisionType = other.collisionType;
    }


    std::unique_ptr<Vector2> size = std::make_unique<Vector2>(Vector2(0, 0));
    CollisionType collisionType;
};

#endif //BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
