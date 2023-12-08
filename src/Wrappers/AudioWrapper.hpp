//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOWRAPPER_HPP
#define BRACK_ENGINE_AUDIOWRAPPER_HPP


#include "Components/Archetypes/AudioArchetype.hpp"
#include <fmod.h>
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

    void playSound(AudioArchetype &audioComponent);

    void pauseSound(AudioArchetype &audioComponent);

    void resumeSound(AudioArchetype &audioComponent);

    bool isValidAudioPath(const AudioArchetype& audioComponent);

    std::string getFileName(const std::string& audioPath);

    int findAvailableSoundEffectsChannel();

    void clearUnusedChannels();

    void clearChannels();

private:
    void playSoundOnChannel(FMOD_CHANNEL *&channel, int channelID, AudioArchetype &audioComponent);
    void pauseChannel(FMOD_CHANNEL* channel, AudioArchetype &audioComponent);
    void resumeChannel(FMOD_CHANNEL* channel, AudioArchetype &audioComponent);
    FMOD_SYSTEM *system;
    std::unordered_map<int, FMOD_CHANNEL*> soundEffectsChannelMap;
    std::pair<int, FMOD_CHANNEL*> soundTrackChannelPair;
    int soundTrackChannel = 10;
};


#endif //BRACK_ENGINE_AUDIOWRAPPER_HPP
