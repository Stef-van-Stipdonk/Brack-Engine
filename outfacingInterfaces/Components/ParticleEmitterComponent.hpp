//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
#define BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP

#include "IComponent.hpp"

struct ParticleEmitterComponent : public IComponent {
    explicit ParticleEmitterComponent(uint32_t entityId) : IComponent(entityId) {}

    ~ParticleEmitterComponent() override = default;

    int amount;
};


#endif //BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
