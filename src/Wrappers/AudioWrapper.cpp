//
// Created by jesse on 31/10/2023.
//

#include <fmod_errors.h>
#include "AudioWrapper.hpp"
#include "../Logger.hpp"


AudioWrapper::AudioWrapper() : system(nullptr) {
    FMOD_RESULT result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        Logger::Error("FMOD system creation failed: " + std::string(FMOD_ErrorString(result)));
    } else {
        result = system->init(32, FMOD_INIT_NORMAL, nullptr); // Use system->init
        if (result != FMOD_OK) {
            Logger::Error("FMOD system initialization failed: " + std::string(FMOD_ErrorString(result)));
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


void AudioWrapper::StartSound(AudioComponent &audioComponent) {
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

    FMOD::Channel* fModChannel = nullptr;
    result = system->playSound(sound, nullptr, false, &fModChannel);

    if (result != FMOD_OK) {
        Logger::Error("Failed to play sound: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Store the FMOD Channel in the AudioComponent
    audioComponent.channel = FindIntChannel(fModChannel);

    // Add the FMOD channel to the channelMap
    channelMap[audioComponent.channel] = fModChannel;
}

void AudioWrapper::StopSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindFMODChannel(audioComponent.channel);

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
    FMOD::Channel* fModChannel = FindFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Check if the fModChannel is playing
    result = fModChannel->isPlaying(&audioComponent.isPlaying);

    if (result != FMOD_OK) {
        Logger::Error("Error checking playback state for the fModChannel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Toggle pause for the fModChannel
    result = fModChannel->setPaused(!audioComponent.isPlaying);

    if (result != FMOD_OK) {
        Logger::Error("Error toggling pause for the fModChannel: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::ResumeSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Resume the fModChannel (unset the pause)
    result = fModChannel->setPaused(false);

    if (result != FMOD_OK) {
        Logger::Error("Error resuming the fModChannel: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::SetVolume(AudioComponent &audioComponent, float volume) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindFMODChannel(audioComponent.channel);

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

void AudioWrapper::SetLooping(AudioComponent &audioComponent, bool loop) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* fModChannel = FindFMODChannel(audioComponent.channel);

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

FMOD::Channel* AudioWrapper::FindFMODChannel(int intChannel) {
    auto it = channelMap.find(intChannel);
    if (it != channelMap.end()) {
        return it->second;
    }
    return nullptr;
}

int AudioWrapper::FindIntChannel(FMOD::Channel *fModChannel) {
    for (const auto &entry : channelMap) {
        if (entry.second == fModChannel) {
            return entry.first;
        }
    }
    // If the FMOD channel is not found, return some default or error value.
    return -1;
}
