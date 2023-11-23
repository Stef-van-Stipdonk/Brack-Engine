//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP
#define BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"

struct RigidBodyComponent : public IComponent {
    explicit RigidBodyComponent() : IComponent() {}

    ~RigidBodyComponent() override = default;

     virtual std::unique_ptr<IComponent> clone() const {
         return std::make_unique<RigidBodyComponent>(*this);
     }

     RigidBodyComponent(const RigidBodyComponent& other) : IComponent(other) {
         mass = other.mass;
         gravityScale = other.gravityScale;
     }

    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    float mass, gravityScale;

};

#endif //BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP
