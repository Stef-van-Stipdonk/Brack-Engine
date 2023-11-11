//
// Created by Jimmy on 11/11/2023.
//

#ifndef BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP
#define BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP

#include "AudioComponent.hpp"

struct SoundTrackComponent : AudioComponent {
    explicit SoundTrackComponent() : AudioComponent(1) {}

    ~SoundTrackComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<SoundTrackComponent>(this);
    }
};

#endif //BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP
