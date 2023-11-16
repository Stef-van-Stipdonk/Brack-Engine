//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOCOMPONENT_HPP
#define BRACK_ENGINE_AUDIOCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include <string>
#include <Components/Archetypes/AudioArchetype.hpp>
#include <utility>

struct AudioComponent : public AudioArchetype {
protected:
    explicit AudioComponent(std::string path, bool looping) : AudioArchetype(), audioPath(std::move(path)), isLooping(looping) {}

public:
    ~AudioComponent() = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<AudioComponent>(*this);
    }


    bool startPlaying = false;
    float volume;
    bool isSoundTrack;

    bool getIsLooping() const {
        return isLooping;
    }

    std::string getAudioPath() const{
        return audioPath;
    }

private:
    const std::string audioPath;
    const bool isLooping;
};

#endif //BRACK_ENGINE_AUDIOCOMPONENT_HPP
