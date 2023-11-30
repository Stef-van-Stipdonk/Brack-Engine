//
// Created by jesse on 31/10/2023.
//


#include <algorithm>
#include "AudioWrapper.hpp"

AudioWrapper::AudioWrapper() : system(nullptr) {
    FMOD_RESULT result = FMOD_System_Create(&system, FMOD_VERSION);
    if (result != FMOD_OK) {
        Logger::Error("FMOD system creation failed: " + std::string(FMOD_ErrorString(result)));
    } else {
        result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, nullptr); // Use system->init
        if (result != FMOD_OK) {
            Logger::Error("FMOD system initialization failed: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

AudioWrapper::~AudioWrapper() {
    if (system) {
        FMOD_RESULT result = FMOD_System_Release(system);
        if (result != FMOD_OK) {
            Logger::Error("Failed to release FMOD system: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

void AudioWrapper::cleanUp() {
    if (system) {
        FMOD_RESULT result = FMOD_System_Release(system);;
        if (result != FMOD_OK) {
            Logger::Error("Failed to release FMOD system: " + std::string(FMOD_ErrorString(result)));
        }
        system = nullptr;
    }
}

int AudioWrapper::findAvailableSoundEffectsChannel() {
    clearUnusedChannels();

    int availableSFXChannels = ConfigSingleton::GetInstance().getAmountOfSoundEffectsChannels();

    if (availableSFXChannels <= 0) {
        Logger::Error("Invalid SFX channel count.");
        return -1;
    }

    for (int i = 0; i < availableSFXChannels; ++i) {
        if (soundEffectsChannelMap.find(i) == soundEffectsChannelMap.end()) {
            return i;
        }
    }
    return -1; // No available channel found
}

void AudioWrapper::clearUnusedChannels() {
    std::vector<int> channelsToRelease;

    for (auto it = soundEffectsChannelMap.begin(); it != soundEffectsChannelMap.end();) {
        FMOD_CHANNEL* channel = it->second;
        int isPlaying = 0; // Declaration without initialization

        // Checking if the channel is playing
        if (channel) {
            FMOD_RESULT result = FMOD_Channel_IsPlaying(channel,&isPlaying);
            if (result != FMOD_OK) {
                Logger::Error("Error checking if channel is playing: " + std::string(FMOD_ErrorString(result)));
                ++it;
                continue;
            }

            Logger::Debug("Channel ID: " + std::to_string(it->first) + ", Is playing: " + (isPlaying ? "true" : "false"));

            if (!isPlaying) {
                channelsToRelease.push_back(it->first); // Marking channel for release
                it = soundEffectsChannelMap.erase(it); // Erasing channel from map
            } else {
                ++it; // Move to the next channel
            }
        } else {
            Logger::Debug("Invalid channel found and removed.");
            it = soundEffectsChannelMap.erase(it); // Erase invalid channel from the map
        }
    }
}

void AudioWrapper::playSound(AudioArchetype &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    if (!isValidAudioPath(audioComponent)) {
        Logger::Error("Invalid audio file path.");
        return;
    }

    if(audioComponent.isSoundTrack){
        soundTrackChannelPair.first = soundTrackChannel; // Set the channel ID

        playSoundOnChannel(soundTrackChannelPair.second, soundTrackChannel, audioComponent);
    }else{
        int availableSFXChannels = ConfigSingleton::GetInstance().getAmountOfSoundEffectsChannels();

        if (availableSFXChannels <= 0) {
            Logger::Error("No available SFX channels.");
            return;
        }

        int channelID = findAvailableSoundEffectsChannel();

        if (channelID == -1) {
            Logger::Debug("All SFX channels are currently in use.");
            return;
        }

        playSoundOnChannel(soundEffectsChannelMap[channelID], channelID, audioComponent);
    }
}

void AudioWrapper::playSoundOnChannel(FMOD_CHANNEL *&channel, int channelID, AudioArchetype &audioComponent) {
    FMOD_SOUND* sound = nullptr;
    FMOD_MODE mode = audioComponent.isSoundTrack ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;
    auto audioPath = ConfigSingleton::GetInstance().GetBaseAssetPath() + audioComponent.getAudioPath();
    FMOD_RESULT result = FMOD_System_CreateSound(system, audioPath.c_str(), mode, 0, &sound);

    if (result != FMOD_OK) {
        Logger::Error("Failed to create sound: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    result = FMOD_System_PlaySound(system, sound, nullptr, false, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Failed to play sound on channel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    FMOD_System_SetUserData(system,reinterpret_cast<void*>(channelID));
    FMOD_Channel_SetVolume(channel, audioComponent.volume);

    Logger::Debug("Uploaded sound to Channel: " + std::to_string(channelID) + ", Path: " + audioPath);
}

void AudioWrapper::pauseChannel(FMOD_CHANNEL *channel, AudioArchetype &audioComponent) {
    if (channel) {
        FMOD_SOUND* sound = nullptr;
        FMOD_RESULT result = FMOD_Channel_GetCurrentSound(channel, &sound);
        if (result != FMOD_OK) {
            Logger::Error("Error getting current sound: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        char audioPath[256];
        result = FMOD_Sound_GetName(sound, audioPath, sizeof(audioPath));
        if (result != FMOD_OK) {
            Logger::Error("Error getting sound name: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        if (std::string(audioPath) == getFileName(audioComponent.getAudioPath())) {
            result = FMOD_Channel_SetPaused(channel, true);
            if (result != FMOD_OK) {
                Logger::Error("Error pausing channel: " + std::string(FMOD_ErrorString(result)));
            }
        }
    }
}

void AudioWrapper::pauseSound(AudioArchetype &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    if(!audioComponent.getIsSoundTrack()){
        for (const auto& it : soundEffectsChannelMap) {
            pauseChannel(it.second, audioComponent);
        }
    }
    else {
        pauseChannel(soundTrackChannelPair.second, audioComponent);
    }
}

void AudioWrapper::resumeChannel(FMOD_CHANNEL *channel, AudioArchetype &audioComponent) {
    if (channel) {
        FMOD_SOUND * sound = nullptr;
        FMOD_RESULT result = FMOD_Channel_GetCurrentSound(channel, &sound);
        if (result != FMOD_OK) {
            Logger::Error("Error getting current sound: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        char audioPath[256];
        result = FMOD_Sound_GetName(sound, audioPath, sizeof(audioPath));
        if (result != FMOD_OK) {
            Logger::Error("Error getting sound name: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        if (std::string(audioPath) == getFileName(audioComponent.getAudioPath())) {
            int isPaused = 0;
            result = FMOD_Channel_GetPaused(channel, &isPaused);
            if (result != FMOD_OK) {
                Logger::Error("Error checking if channel is paused: " + std::string(FMOD_ErrorString(result)));
                return;
            }

            if (isPaused) {
                result = FMOD_Channel_SetPaused(channel, false); // Resume the channel
                if (result != FMOD_OK) {
                    Logger::Error("Error resuming channel: " + std::string(FMOD_ErrorString(result)));
                }
            }
        }
    }
}

void AudioWrapper::resumeSound(AudioArchetype &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    int anySoundsPaused = 0;
    for (auto & it : soundEffectsChannelMap) {
        FMOD_CHANNEL* channel = it.second;
        if (channel) {
            int isPlaying = 0;
            FMOD_RESULT result = FMOD_Channel_IsPlaying(channel, &isPlaying);
            if (result != FMOD_OK) {
                Logger::Error("Error checking if channel is playing: " + std::string(FMOD_ErrorString(result)));
                continue;
            }
            if (!isPlaying) {
                anySoundsPaused = 1;
                Logger::Debug("Paused Sound Found");
                break; // Exit the loop as soon as a paused sound is found
            }
        }
    }
    if(!anySoundsPaused){
        FMOD_Channel_IsPlaying(soundTrackChannelPair.second, &anySoundsPaused);
    }

    if (!anySoundsPaused) {
        return;
    }

    if (!audioComponent.getIsSoundTrack()) {
        for (const auto& it : soundEffectsChannelMap) {
            resumeChannel(it.second, audioComponent);
        }
    } else {
        resumeChannel(soundTrackChannelPair.second, audioComponent);
    }
}

bool AudioWrapper::isValidAudioPath(const AudioArchetype& audioComponent){
    std::ifstream file(ConfigSingleton::GetInstance().GetBaseAssetPath() + audioComponent.getAudioPath());

    if (!file.good()) {
        Logger::Error("Audio file not found at path: " + audioComponent.getAudioPath());
        return false;
    }

    // Extract the file extension
    size_t dotIndex = audioComponent.getAudioPath().find_last_of('.');
    if (dotIndex == std::string::npos) {
        Logger::Error("Invalid audio file path (no file extension): " + audioComponent.getAudioPath());
        return false;
    }

    std::string extension = audioComponent.getAudioPath().substr(dotIndex + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // List of common audio file extensions
    const std::vector<std::string> audioExtensions = {"mp3", "wav", "ogg", "flac", "aac", "m4a"};

    // Check if the extension is in the list of common audio file extensions
    if (std::find(audioExtensions.begin(), audioExtensions.end(), extension) == audioExtensions.end()) {
        Logger::Error("Invalid audio file extension at path: " + audioComponent.getAudioPath());
        return false;
    }

    return true;
}

std::string AudioWrapper::getFileName(const std::string& audioPath) {
    size_t lastSlash = audioPath.find_last_of("/\\");
    std::string fileName = audioPath.substr(lastSlash + 1);

    return fileName;
}
