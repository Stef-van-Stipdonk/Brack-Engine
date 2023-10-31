//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
#define BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP

#include "IComponent.hpp"

struct ParticleEmitterComponent : public IComponent {
    ParticleEmitterComponent() = default;

    ~ParticleEmitterComponent() override = default;

    int amount;
};


#endif //BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
