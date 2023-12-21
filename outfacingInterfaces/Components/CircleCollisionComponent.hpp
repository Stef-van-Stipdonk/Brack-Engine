//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP

#include <memory>
#include "Archetypes/CollisionArchetype.hpp"

struct CircleCollisionComponent : public CollisionArchetype {

    explicit CircleCollisionComponent(float radius)
            : CollisionArchetype(), radius(radius) {}

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<CircleCollisionComponent>(*this);
    }

    ~CircleCollisionComponent() override {};

    CircleCollisionComponent(const CircleCollisionComponent &other) : CollisionArchetype(other) {
        radius = other.radius;
    }

    float radius;
};

#endif //BRACK_ENGINE_CIRCLECOLLISIONCOMPONENT_HPP
