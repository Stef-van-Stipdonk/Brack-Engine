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

void AudioWrapper::StopSound(int channelIndex) {
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

    // Stop the channel
    result = channel->stop();

    if (result != FMOD_OK) {
        Logger::Error("Error stopping channel " + std::to_string(channelIndex) + ": " + std::string(FMOD_ErrorString(result)));
    }
}

void AudioWrapper::PauseChannel(int channelIndex) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    FMOD_RESULT result;
    bool isPlaying = false;
    FMOD::Channel* channel = nullptr;

    // Get the channel associated with the index
    result = system->getChannel(channelIndex, &channel);

    if (result != FMOD_OK) {
        Logger::Error("Error getting channel: " + std::string(FMOD_ErrorString(result)));
        return;
    }

    // Check if the channel is playing
    result = channel->isPlaying(&isPlaying);

    if (result != FMOD_OK) {
        Logger::Error("Error checking playback state for channel " + std::to_string(channelIndex) + ": " + std::string(FMOD_ErrorString(result)));
        return;
    }

    if (isPlaying) {
        // Pause the channel if it's currently playing
        result = channel->setPaused(true);
        if (result != FMOD_OK) {
            Logger::Error("Error pausing channel " + std::to_string(channelIndex) + ": " + std::string(FMOD_ErrorString(result)));
        }
    }
}

void AudioWrapper::ResumeChannel(int channelIndex) {
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

    // Resume the channel (unset the pause)
    result = channel->setPaused(false);

    if (result != FMOD_OK) {
        Logger::Error("Error resuming channel " + std::to_string(channelIndex) + ": " + std::string(FMOD_ErrorString(result)));
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

void AudioWrapper::SetLooping(int channelIndex, bool loop) {
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

    // Set the looping mode for the channel
    result = channel->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

    if (result != FMOD_OK) {
        Logger::Error("Error setting looping mode for channel " + std::to_string(channelIndex) + ": " + std::string(FMOD_ErrorString(result)));
    }
}

