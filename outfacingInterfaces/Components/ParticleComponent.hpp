//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLECOMPONENT_HPP
#define BRACK_ENGINE_PARTICLECOMPONENT_HPP

#include "IComponent.hpp"

class ParticleComponent : public IComponent {
public:
    ParticleComponent() = default;

    ~ParticleComponent() override = default;

    float lifetimeInSeconds;
};


#endif //BRACK_ENGINE_PARTICLECOMPONENT_HPP
