//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLECOMPONENT_HPP
#define BRACK_ENGINE_PARTICLECOMPONENT_HPP

#include "IComponent.hpp"

struct ParticleComponent : public IComponent {
    explicit ParticleComponent(uint32_t entityId) : IComponent(entityId) {}

    ~ParticleComponent() override = default;

    float lifetimeInSeconds;
};


#endif //BRACK_ENGINE_PARTICLECOMPONENT_HPP
