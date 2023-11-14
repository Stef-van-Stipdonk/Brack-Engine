//
// Created by jesse on 31/10/2023.
//

#include <fmod_errors.h>
#include <algorithm>
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

    // Stop the fModChannel without erasing it from the map
    result = fModChannel->stop();

    if (result != FMOD_OK) {
        Logger::Error("Error stopping the fModChannel: " + std::string(FMOD_ErrorString(result)));
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

    // Get the duration of the sound
    unsigned int length;
    result = sound->getLength(&length, FMOD_TIMEUNIT_MS);

    if (result != FMOD_OK) {
        Logger::Error("Failed to get sound duration: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    audioComponent.duration = length;

    FMOD::Channel* channel = nullptr;

    if (audioComponent.isSoundTrack) {
        result = system->playSound(sound, nullptr, true, &soundTrackChannelPair.second);
        if (result != FMOD_OK) {
            Logger::Error("Failed to play sound on the soundtrack channel: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        // Set the channel's ID
        soundTrackChannelPair.second->setUserData(reinterpret_cast<void*>(soundTrackChannelPair.first));

        Logger::Debug("Uploaded sound to Soundtrack Channel: " + std::to_string(soundTrackChannelPair.first) + ", Path: " + audioComponent.audioPath);
    } else {
        int channelID = audioComponent.channel;

        if (channelID == soundTrackChannelPair.first) {
            Logger::Error("Cannot upload sound to the Soundtrack Channel using a regular channel.");
            return;
        }

        // Create a channel for the sound
        result = system->playSound(sound, nullptr, true, &channel);

        if (result != FMOD_OK) {
            Logger::Error("Failed to play sound: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        // Set the channel's ID
        channel->setUserData(reinterpret_cast<void*>(channelID));

        // Add the channel to the map
        soundEffectsChannelMap[channelID] = channel;

        Logger::Debug("Uploaded sound to Channel: " + std::to_string(channelID) + ", Path: " + audioComponent.audioPath);
    }
}

void AudioWrapper::RemoveSound(AudioComponent &audioComponent) {
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
        auto it = soundEffectsChannelMap.find(audioComponent.channel);
        if (it != soundEffectsChannelMap.end()) {
            soundEffectsChannelMap.erase(it);
        } else {
            Logger::Error("Channel ID not found in soundEffectsChannelMap.");
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

void AudioWrapper::PlaySound(AudioComponent &audioComponent) {
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

bool AudioWrapper::HasSoundFinished(const AudioComponent& audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return false;
    }

    FMOD::Channel* fModChannel = FindAssociatedFMODChannel(audioComponent.channel);

    if (!fModChannel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return false;
    }

    bool isPlaying;
    if (fModChannel->isPlaying(&isPlaying) != FMOD_OK || !isPlaying) {
        // If the channel is not playing, consider it finished
        return true;
    }

    unsigned int currentPosition;
    FMOD_RESULT result = fModChannel->getPosition(&currentPosition, FMOD_TIMEUNIT_MS);

    if (result != FMOD_OK) {
        Logger::Error("Error getting position for the fModChannel: " + std::string(FMOD_ErrorString(result)));
        return false;
    }

    // Compare the current position with the total duration of the sound
    return currentPosition >= audioComponent.duration;
}

FMOD::Channel* AudioWrapper::FindAssociatedFMODChannel(int intChannel) {
    auto it = soundEffectsChannelMap.find(intChannel);
    if (it != soundEffectsChannelMap.end()) {
        return it->second;
    }

    if (intChannel == soundTrackChannel) {
        return soundTrackChannelPair.second;
    }

    return nullptr;
}

bool AudioWrapper::IsInitialized(const AudioComponent& audioComponent) {
    int channelID = audioComponent.channel;

    auto it = soundEffectsChannelMap.find(channelID);
    return (it != soundEffectsChannelMap.end());
}

bool AudioWrapper::IsValidAudioPath(const AudioComponent& audioComponent){
    std::ifstream file(audioComponent.audioPath);

    if (!file.good()) {
        Logger::Error("Audio file not found at path: " + audioComponent.audioPath);
        return false;
    }

    // Extract the file extension
    size_t dotIndex = audioComponent.audioPath.find_last_of('.');
    if (dotIndex == std::string::npos) {
        Logger::Error("Invalid audio file path (no file extension): " + audioComponent.audioPath);
        return false;
    }

    std::string extension = audioComponent.audioPath.substr(dotIndex + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // List of common audio file extensions
    const std::vector<std::string> audioExtensions = {"mp3", "wav", "ogg", "flac", "aac", "m4a"};

    // Check if the extension is in the list of common audio file extensions
    if (std::find(audioExtensions.begin(), audioExtensions.end(), extension) == audioExtensions.end()) {
        Logger::Error("Invalid audio file extension at path: " + audioComponent.audioPath);
        return false;
    }

    return true;
}

