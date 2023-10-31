//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP
#define BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP

#include "IComponent.hpp"

class RigidBodyComponent : public IComponent {
public:
    RigidBodyComponent() = default;

    ~RigidBodyComponent() override = default;

    float mass, gravityScale;

};

#endif //BRACK_ENGINE_RIGIDBODYCOMPONENT_HPP
