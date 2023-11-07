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

void AudioWrapper::StopSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = audioComponent.channel;

    if (!channel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Stop the channel
    result = channel->stop();

    if (result != FMOD_OK) {
        Logger::Error("Error stopping the channel: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::StopAll() {
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

void AudioWrapper::PauseSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = audioComponent.channel;

    if (!channel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Check if the channel is playing
    result = channel->isPlaying(&audioComponent.isPlaying);

    if (result != FMOD_OK) {
        Logger::Error("Error checking playback state for the channel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Toggle pause for the channel
    result = channel->setPaused(!audioComponent.isPlaying);

    if (result != FMOD_OK) {
        Logger::Error("Error toggling pause for the channel: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::PauseAll() {
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

void AudioWrapper::ResumeSound(AudioComponent &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = audioComponent.channel;

    if (!channel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Resume the channel (unset the pause)
    result = channel->setPaused(false);

    if (result != FMOD_OK) {
        Logger::Error("Error resuming the channel: " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::ResumeAll() {
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

void AudioWrapper::SetVolume(AudioComponent &audioComponent, float volume) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = audioComponent.channel;

    if (!channel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Set the volume for the channel
    result = channel->setVolume(volume);

    if (result != FMOD_OK) {
        Logger::Error("Error setting volume for the channel: " + std::string(FMOD_ErrorString(result)));
    }

    audioComponent.volume = volume;
}

void AudioWrapper::SetVolumeAll(float volume) {
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

void AudioWrapper::SetLooping(AudioComponent &audioComponent, bool loop) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    FMOD::Channel* channel = audioComponent.channel;

    if (!channel) {
        Logger::Error("Channel in AudioComponent is not initialized.");
        return;
    }

    // Set the looping mode for the channel
    result = channel->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

    if (result != FMOD_OK) {
        Logger::Error("Error setting looping mode for the channel: " + std::string(FMOD_ErrorString(result)));
    }

    audioComponent.isLooping = loop;
}

