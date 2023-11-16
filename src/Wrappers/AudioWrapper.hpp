//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOWRAPPER_HPP
#define BRACK_ENGINE_AUDIOWRAPPER_HPP


#include "Components/AudioComponent.hpp"
#include "../../lib/FMod/include/fmod.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include "../ConfigSingleton.hpp"

class AudioWrapper {
public:
    AudioWrapper();

    ~AudioWrapper();

    void CleanUp();

    void PlaySound(AudioComponent &audioComponent);

    bool IsValidAudioPath(const AudioComponent& audioComponent);

    int FindAvailableSFXChannel() const;

private:
    FMOD::System *system;
    std::unordered_map<int, FMOD::Channel*> soundEffectsChannelMap;
    std::pair<int, FMOD::Channel*> soundTrackChannelPair;
    int soundTrackChannel = 10;
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
