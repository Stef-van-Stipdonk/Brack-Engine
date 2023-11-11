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

    void StopSound(AudioComponent &audioComponent);

    void PauseSound(AudioComponent &audioComponent);

    void ResumeSound(AudioComponent &audioComponent);

    float GetVolume(AudioComponent &audioComponent);

    void SetVolume(AudioComponent &audioComponent, float volume);

    bool GetLooping(const AudioComponent &audioComponent) ;

    void SetLooping(AudioComponent &audioComponent, bool loop);

    const std::unordered_map<int, bool>& GetPlaybackStateMap() const;

    void SetPlaybackState(int entityID, bool state);

private:
    FMOD::System *system;
    std::unordered_map<int, FMOD::Channel*> channelMap;
    std::unordered_map<int, bool> playbackStateMap;
    FMOD::Channel* FindAssociatedFMODChannel(int intChannel);
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
