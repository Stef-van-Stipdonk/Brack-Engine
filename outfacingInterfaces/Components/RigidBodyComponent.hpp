//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP
#define BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP

#include "IComponent.hpp"

struct RigidBodyComponent : public IComponent {
    explicit RigidBodyComponent( ) : IComponent() {}

    ~RigidBodyComponent() override = default;

    float mass, gravityScale;

};

#endif //BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP
