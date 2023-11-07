//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOWRAPPER_HPP
#define BRACK_ENGINE_AUDIOWRAPPER_HPP


#include "Components/AudioComponent.hpp"
#include <vector>
#include <fmod.h>
#include <memory>

class AudioWrapper {
public:
    AudioWrapper();

    ~AudioWrapper();

    void StartSound(AudioComponent &audioComponent);

    void StopSoundChannel(int channelID);

    void StopAllSoundChannels();

    void PauseChannel(int channelID);

    void PauseAllSoundChannels();

    void ResumeChannel(int channelID);

    void ResumeAllSoundChannels();

    void SetVolume(int channelID, float volume);

    void SetAllVolume(float volume);

    float GetVolume(int channelId);

    void SetLooping(int channelID, bool loop);

private:
    FMOD::System *system;
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
