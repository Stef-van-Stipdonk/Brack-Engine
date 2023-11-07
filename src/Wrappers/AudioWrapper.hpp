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

    void StopSound(AudioComponent &audioComponent);

    void PauseSound(AudioComponent &audioComponent);

    void ResumeSound(AudioComponent &audioComponent);

    void SetVolume(AudioComponent &audioComponent, float volume);

    void SetLooping(AudioComponent &audioComponent, bool loop);

private:
    FMOD::System *system;
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
