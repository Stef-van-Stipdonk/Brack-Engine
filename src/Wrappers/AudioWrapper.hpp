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

    void TogglePauseChannel(int channelIndex);

    void StopPauseChannel(int channelIndex);

    AudioWrapper(const AudioWrapper &other);

private:
    FMOD_SYSTEM *system;
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
