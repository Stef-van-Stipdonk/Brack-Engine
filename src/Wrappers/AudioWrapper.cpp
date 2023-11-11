//
// Created by jesse on 31/10/2023.
//

#include <fmod_errors.h>
#include "AudioWrapper.hpp"


AudioWrapper::AudioWrapper() : system(nullptr) {
    FMOD_RESULT result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        Logger::Error("FMOD system creation failed: " + std::string(FMOD_ErrorString(result)));
    } else {
        result = system->init(32, FMOD_INIT_NORMAL, nullptr); // Use system->init
        if (result != FMOD_OK) {
            Logger::Error("FMOD system initialization failed: " + std::string(FMOD_ErrorString(result)));
        }

        // Initialize soundTrackChannel to be channel 1
        result = system->getChannel(soundTrackChannelID, &soundTrackChannel);
        if (result != FMOD_OK) {
            Logger::Error("Failed to get soundTrack channel: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

AudioWrapper::~AudioWrapper() {
    if (system) {
        FMOD_RESULT result = system->release();
        if (result != FMOD_OK) {
            Logger::Error("Failed to release FMOD system: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

void AudioWrapper::CleanUp() {
    if (system) {
        FMOD_RESULT result = system->release();
        if (result != FMOD_OK) {
            Logger::Error("Failed to release FMOD system: " + std::string(FMOD_ErrorString(result)));
        }
        system = nullptr;
    }
}


void AudioWrapper::UploadSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = system->createSound(audioComponent.audioPath.c_str(), FMOD_DEFAULT, 0, &sound);

    if (result != FMOD_OK) {
        Logger::Error("Failed to create sound: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    int channelID = audioComponent.channel;

    // Create a channel for the sound
    FMOD::Channel* channel = nullptr;
    result = system->playSound(sound, nullptr, true, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Failed to play sound: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Set the channel's ID
    channel->setUserData(reinterpret_cast<void*>(channelID));

    // Add the channel to the map
    channelMap[channelID] = channel;
    playbackStateMap[channelID] = false;
    SetPlaybackState(channelID, false);


    Logger::Debug("Uploaded sound to Channel: " + std::to_string(channelID) + ", Path: " + audioComponent.audioPath);
}

void AudioWrapper::StopSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindAssociatedFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Stop the fModChannel
    result = fModChannel->stop();

    if (result == FMOD_OK) {
        // Erase the channel from the map
        auto it = channelMap.find(audioComponent.channel);
        if (it != channelMap.end()) {
            channelMap.erase(it);

            // Set the playback state to false
            playbackStateMap[audioComponent.channel] = false;
        } else {
            Logger::Error("Channel ID not found in channelMap.");
        }
    } else {
        Logger::Error("Error stopping the fModChannel: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::PauseSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindAssociatedFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Check if the fModChannel is playing
    bool isPlaying;
    result = fModChannel->isPlaying(&isPlaying);

    if (result != FMOD_OK) {
        Logger::Error("Error checking playback state for the fModChannel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Only toggle pause if the sound is currently playing
    if (isPlaying) {
        result = fModChannel->setPaused(true);
        if (result != FMOD_OK) {
            Logger::Error("Error pausing the fModChannel: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

void AudioWrapper::ResumeSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindAssociatedFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Check if the fModChannel is paused
    bool isPaused;
    result = fModChannel->getPaused(&isPaused);

    if (result != FMOD_OK) {
        Logger::Error("Error checking pause state for the fModChannel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Only resume if the sound is currently paused
    if (isPaused) {
        result = fModChannel->setPaused(false);
        if (result != FMOD_OK) {
            Logger::Error("Error resuming the fModChannel: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

float AudioWrapper::GetVolume(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return 0.0f; // Return some default value or handle the error as needed
    }

    FMOD::Channel* fModChannel = FindAssociatedFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return 0.0f; // Return some default value or handle the error as needed
    }

    float volume;
    FMOD_RESULT result = fModChannel->getVolume(&volume);

    if (result != FMOD_OK) {
        Logger::Error("Error getting volume for the fModChannel: " + std::string(FMOD_ErrorString(result)));
        return 0.0f; // Return some default value or handle the error as needed
    }

    return volume;
}

void AudioWrapper::SetVolume(AudioComponent &audioComponent, float volume) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindAssociatedFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Set the volume for the fModChannel
    result = fModChannel->setVolume(volume);

    if (result != FMOD_OK) {
        Logger::Error("Error setting volume for the fModChannel: " + std::string(FMOD_ErrorString(result)));
    }
}

bool AudioWrapper::GetLooping(const AudioComponent &audioComponent)  {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return false;  // or handle accordingly
    }

    FMOD::Channel* fModChannel = FindAssociatedFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return false;  // or handle accordingly
    }

    // Get the mode for the fModChannel
    FMOD_MODE mode;
    FMOD_RESULT result = fModChannel->getMode(&mode);

    if (result != FMOD_OK) {
        Logger::Error("Error getting mode for the fModChannel: " + std::string(FMOD_ErrorString(result)));
        return false;  // or handle accordingly
    }

    return ((mode & FMOD_LOOP_NORMAL) != 0);
}

void AudioWrapper::SetLooping(AudioComponent &audioComponent, bool loop) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindAssociatedFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Set the looping mode for the fModChannel
    result = fModChannel->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

    if (result != FMOD_OK) {
        Logger::Error("Error setting looping mode for the fModChannel: " + std::string(FMOD_ErrorString(result)));
    }
}

FMOD::Channel* AudioWrapper::FindAssociatedFMODChannel(int intChannel) {
    auto it = channelMap.find(intChannel);
    if (it != channelMap.end()) {
        return it->second;
    }
    return nullptr;
}

const std::unordered_map<int, bool>& AudioWrapper::GetPlaybackStateMap() const {
    return playbackStateMap;
}

void AudioWrapper::SetPlaybackState(int channelID, bool state) {
    playbackStateMap[channelID] = state;
}

int AudioWrapper::GetSoundTrackChannelID() {
    return soundTrackChannelID;
}