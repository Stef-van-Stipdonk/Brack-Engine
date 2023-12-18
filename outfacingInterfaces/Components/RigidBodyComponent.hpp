//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP
#define BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP

#include "IComponent.hpp"
#include <Helpers/CollisionType.hpp>
#include <Helpers/Vector2.hpp>

struct RigidBodyComponent : public IComponent {
    explicit RigidBodyComponent(CollisionType type) : IComponent(), collisionType(type) {}

    explicit RigidBodyComponent() : IComponent(), collisionType(CollisionType::STATIC) {}

    ~RigidBodyComponent() override = default;

    virtual std::unique_ptr<IComponent> clone() const {
        return std::make_unique<RigidBodyComponent>(*this);
    }

    RigidBodyComponent(const RigidBodyComponent &other) : IComponent(other) {
        mass = other.mass;
        gravityScale = other.gravityScale;
        collisionType = other.collisionType;
        restitution = other.restitution;
        friction = other.friction;
    }


    float mass = 1.0f, gravityScale = 1.0f, restitution = 0.0f, friction = 0.0f;
    CollisionType collisionType;
    std::unique_ptr<Vector2> force = std::make_unique<Vector2>(0, 0);
};

#endif //BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP
