//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOCOMPONENT_HPP
#define BRACK_ENGINE_AUDIOCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include <string>
#include <Components/Archetypes/AudioArchetype.hpp>

struct AudioComponent : public AudioArchetype {

    explicit AudioComponent() : AudioArchetype() {}

    ~AudioComponent() = default;

    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<AudioComponent>(*this);
    }

    AudioComponent(const AudioComponent &other) : AudioArchetype(other) {
        audioPath = other.audioPath;
        isLooping = other.isLooping;
        isPlaying = other.isPlaying;
        volume = other.volume;
        channel = other.channel;
    }

    std::string audioPath;
    bool isLooping, isPlaying;
    float volume;
    int channel;
};

#endif //BRACK_ENGINE_AUDIOCOMPONENT_HPP
