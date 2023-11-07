//
// Created by jesse on 31/10/2023.
//

#include <fmod_errors.h>
#include "AudioWrapper.hpp"
#include "../Logger.hpp"


AudioWrapper::AudioWrapper() {
    FMOD_RESULT result = FMOD::System_Create(&system); // Use FMOD::System_Create
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

    FMOD::Channel* channel = nullptr;
    result = system->playSound(sound, nullptr, false, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Failed to play sound: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Store the FMOD Channel in the AudioComponent
    audioComponent.channel = channel;
}

void AudioWrapper::StopSoundChannel(int channelID) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = nullptr;

    // Get the channel associated with the index
    result = system->getChannel(channelID, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Error getting channel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Stop the channel
    result = channel->stop();

    if (result != FMOD_OK) {
        Logger::Error("Error stopping channel " + std::to_string(channelID) + ": " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::StopAllSoundChannels() {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::ChannelGroup* masterGroup = nullptr;

    // Get the master channel group
    result = system->getMasterChannelGroup(&masterGroup);

    if (result != FMOD_OK) {
        Logger::Error("Error getting master channel group: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Stop all channels in the master group
    result = masterGroup->stop();

    if (result != FMOD_OK) {
        Logger::Error("Error stopping all sound channels: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::PauseChannel(int channelID) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    bool isPlaying = false;
    FMOD::Channel* channel = nullptr;

    // Get the channel associated with the index
    result = system->getChannel(channelID, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Error getting channel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Check if the channel is playing
    result = channel->isPlaying(&isPlaying);

    if (result != FMOD_OK) {
        Logger::Error("Error checking playback state for channel " + std::to_string(channelID) + ": " + std::string(FMOD_ErrorString(result)));
        return;
    }

    if (isPlaying) {
        // Pause the channel if it's currently playing
        result = channel->setPaused(true);
        if (result != FMOD_OK) {
            Logger::Error("Error pausing channel " + std::to_string(channelID) + ": " + std::string(FMOD_ErrorString(result)));
        }
    }
}

void AudioWrapper::PauseAllSoundChannels() {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::ChannelGroup* masterGroup = nullptr;

    // Get the master channel group
    result = system->getMasterChannelGroup(&masterGroup);

    if (result != FMOD_OK) {
        Logger::Error("Error getting master channel group: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Pause all channels in the master group
    result = masterGroup->setPaused(true);

    if (result != FMOD_OK) {
        Logger::Error("Error pausing all sound channels: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::ResumeChannel(int channelID) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = nullptr;

    // Get the channel associated with the index
    result = system->getChannel(channelID, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Error getting channel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Resume the channel (unset the pause)
    result = channel->setPaused(false);

    if (result != FMOD_OK) {
        Logger::Error("Error resuming channel " + std::to_string(channelID) + ": " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::ResumeAllSoundChannels() {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::ChannelGroup* masterGroup = nullptr;

    // Get the master channel group
    result = system->getMasterChannelGroup(&masterGroup);

    if (result != FMOD_OK) {
        Logger::Error("Error getting master channel group: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Resume all channels in the master group
    result = masterGroup->setPaused(false);

    if (result != FMOD_OK) {
        Logger::Error("Error resuming all sound channels: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::SetVolume(int channelIndex, float volume) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = nullptr;

    // Get the channel associated with the index
    result = system->getChannel(channelIndex, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Error getting channel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Set the volume for the channel
    result = channel->setVolume(volume);

    if (result != FMOD_OK) {
        Logger::Error("Error setting volume for channel " + std::to_string(channelIndex) + ": " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::SetAllVolume(float volume) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::ChannelGroup* masterGroup = nullptr;

    // Get the master channel group
    result = system->getMasterChannelGroup(&masterGroup);

    if (result != FMOD_OK) {
        Logger::Error("Error getting master channel group: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Set the volume for all channels in the master group
    result = masterGroup->setVolume(volume);

    if (result != FMOD_OK) {
        Logger::Error("Error setting volume for all sound channels: " + std::string(FMOD_ErrorString(result)));
    }
}

float AudioWrapper::GetVolume(int channelId) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return -1.0f; // Return a default value or handle the error as needed.
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = nullptr;
    float volume = -1.0f; // Initialize with a default value.

    // Get the channel associated with the channelId
    result = system->getChannel(channelId, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Error getting channel: " + std::string(FMOD_ErrorString(result)));
        return volume; // Return the default value or handle the error as needed.
    }

    // Get the volume of the channel
    result = channel->getVolume(&volume);

    if (result != FMOD_OK) {
        Logger::Error("Error getting volume for channel " + std::to_string(channelId) + ": " + std::string(FMOD_ErrorString(result)));
        return volume; // Return the default value or handle the error as needed.
    }

    return volume;
}

void AudioWrapper::SetLooping(int channelID, bool loop) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = nullptr;

    // Get the channel associated with the index
    result = system->getChannel(channelID, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Error getting channel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Set the looping mode for the channel
    result = channel->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

    if (result != FMOD_OK) {
        Logger::Error("Error setting looping mode for channel " + std::to_string(channelID) + ": " + std::string(FMOD_ErrorString(result)));
    }
}

