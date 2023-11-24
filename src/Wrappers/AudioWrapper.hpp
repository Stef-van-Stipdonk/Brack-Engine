//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOWRAPPER_HPP
#define BRACK_ENGINE_AUDIOWRAPPER_HPP


#include "Components/Archetypes/AudioArchetype.hpp"
#include "fmod.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include "../ConfigSingleton.hpp"
#include <fmod_errors.h>

class AudioWrapper {
public:
    AudioWrapper();

    ~AudioWrapper();

    void cleanUp();

    void playSoundEffect(AudioArchetype &audioComponent);

    void playSoundTrack(AudioArchetype &audioComponent);

    void pauseSound(AudioArchetype &audioComponent);

    void resumeSound(AudioArchetype &audioComponent);

    bool isValidAudioPath(const AudioArchetype& audioComponent);

    std::string getFileName(const std::string& audioPath);

    int findAvailableSoundEffectsChannel();

    void clearUnusedChannels() ;

private:
    FMOD::System *system;
    std::unordered_map<int, FMOD::Channel*> soundEffectsChannelMap;
    std::pair<int, FMOD::Channel*> soundTrackChannelPair;
    int soundTrackChannel = 10;
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
