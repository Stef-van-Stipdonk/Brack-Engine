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
    explicit AudioComponent(std::string path, bool isSoundTrack) : AudioArchetype(), audioPath(std::move(path)), isSoundTrack(isSoundTrack) {}

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

    bool getIsSoundTrack() const {
        return isSoundTrack;
    }

    std::string getAudioPath() const{
        return audioPath;
    }

private:
    const std::string audioPath;
    const bool isSoundTrack;
};

#endif //BRACK_ENGINE_AUDIOCOMPONENT_HPP
