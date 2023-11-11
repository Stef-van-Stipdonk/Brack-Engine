//
// Created by Jimmy on 11/11/2023.
//

#ifndef BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP
#define BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP

#include "AudioComponent.hpp"

struct SoundEffectComponent : AudioComponent {
    explicit SoundEffectComponent() : AudioComponent(2) {}

    ~SoundEffectComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<SoundEffectComponent>(this);
    }
};

#endif //BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP
