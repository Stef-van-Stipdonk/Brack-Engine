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

    void UploadSound(AudioComponent &audioComponent);

    void RemoveSound(AudioComponent &audioComponent);

    void PauseSound(AudioComponent &audioComponent);

    void PlaySound(AudioComponent &audioComponent);

    void StopSound(AudioComponent &audioComponent);

    float GetVolume(AudioComponent &audioComponent);

    void SetVolume(AudioComponent &audioComponent, float volume);

    bool GetLooping(const AudioComponent &audioComponent) ;

    void SetLooping(AudioComponent &audioComponent, bool loop);

    bool HasSoundFinished(const AudioComponent& audioComponent);

    bool IsInitialized(const AudioComponent& audioComponent);

    bool IsValidAudioPath(const AudioComponent& audioComponent);

private:
    FMOD::System *system;
    std::unordered_map<int, FMOD::Channel*> channelMap;
    FMOD::Channel* FindAssociatedFMODChannel(int intChannel);
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
