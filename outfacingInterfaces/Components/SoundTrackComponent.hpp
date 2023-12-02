//
// Created by Jimmy on 16/11/2023.
//

#ifndef BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP
#define BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP


#include "Archetypes/AudioArchetype.hpp"

struct SoundTrackComponent : public AudioArchetype {
public:
    SoundTrackComponent(std::string path)
            : AudioArchetype(std::move(path), true) {}

    ~SoundTrackComponent() = default;

    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<SoundTrackComponent>(*this);
    }

};


#endif //BRACKOCALYPSE_SOUNDTRACKCOMPONENT_HPP
