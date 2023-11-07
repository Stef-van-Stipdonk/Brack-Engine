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

    void StopSound(int channelIndex);

    void PauseChannel(int channelIndex);

    void ResumeChannel(int channelIndex);

    void SetVolume(int channelIndex, float volume);

    void SetLooping(int channelIndex, bool loop);

private:
    FMOD::System *system;
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
