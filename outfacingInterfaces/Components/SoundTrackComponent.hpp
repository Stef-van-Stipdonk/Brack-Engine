//
// Created by Jimmy on 16/11/2023.
//

#ifndef BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP
#define BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP


#include "AudioComponent.hpp"

struct SoundTrackComponent : public AudioComponent {
    SoundTrackComponent(std::string path)
            : AudioComponent(std::move(path), true) {}

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<SoundTrackComponent>(*this);
    }

};


#endif //BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP
