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


class AudioWrapper {
public:
    AudioWrapper();

    ~AudioWrapper();

    void CleanUp();

    void StartSound(AudioComponent &audioComponent);

    void StopSound(AudioComponent &audioComponent);

    void PauseSound(AudioComponent &audioComponent);

    void ResumeSound(AudioComponent &audioComponent);

    void SetVolume(AudioComponent &audioComponent, float volume);

    void SetLooping(AudioComponent &audioComponent, bool loop);

private:
    FMOD::System *system;

    std::unordered_map<int, FMOD::Channel*> channelMap;
    FMOD::Channel* FindFMODChannel(int intChannel);
    int FindIntChannel(FMOD::Channel* fmodChannel);
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
