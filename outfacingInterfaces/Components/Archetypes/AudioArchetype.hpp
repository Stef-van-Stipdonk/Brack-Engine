//
// Created by Stef van Stipdonk on 12/11/2023.
//

#ifndef BRACKOCALYPSE_AUDIOARCHETYPE_HPP
#define BRACKOCALYPSE_AUDIOARCHETYPE_HPP

#include <Components/IComponent.hpp>
#include "../../../src/Components/ComponentVisitor.hpp"

struct AudioArchetype : public IComponent {
public:
    explicit AudioArchetype(std::string path, bool isSoundTrack) : IComponent(), audioPath(std::move(path)), isSoundTrack(isSoundTrack) {}

    ~AudioArchetype() override = default;

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<AudioArchetype>(*this);
    }


    AudioArchetype(const AudioArchetype &other) : IComponent(other), isSoundTrack(other.isSoundTrack) {}

    void accept(ComponentVisitor &visitor) override {

        visitor.visit(*this);
    }

    bool pauseSound = false;
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

#endif //BRACKOCALYPSE_AUDIOARCHETYPE_HPP
