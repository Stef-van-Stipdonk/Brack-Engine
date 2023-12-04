//
// Created by Stef van Stipdonk on 12/11/2023.
//

#ifndef BRACKOCALYPSE_AUDIOARCHETYPE_HPP
#define BRACKOCALYPSE_AUDIOARCHETYPE_HPP

#include <Components/IComponent.hpp>
#include <string>

struct AudioArchetype : public IComponent {
public:
    explicit AudioArchetype(std::string path, bool isSoundTrack)
            : IComponent(), audioPath(std::move(path)), isSoundTrack(isSoundTrack) {}

    ~AudioArchetype() override = default;

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<AudioArchetype>(*this);
    }


    AudioArchetype(const AudioArchetype &other) :
            IComponent(other),
            audioPath(other.audioPath),
            isSoundTrack(other.isSoundTrack),
            pauseSound(other.pauseSound),
            startPlaying(other.startPlaying),
            volume(other.volume) {}

    bool pauseSound = false;
    bool startPlaying = false;
    float volume;
    const std::string audioPath;
    bool isSoundTrack;

    bool getIsSoundTrack() const {
        return isSoundTrack;
    }

    std::string getAudioPath() const {
        return audioPath;
    }
};

#endif //BRACKOCALYPSE_AUDIOARCHETYPE_HPP
