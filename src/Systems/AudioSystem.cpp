//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"
#include "fmod.hpp"
#include "../includes/ComponentStore.hpp"
#include "fmod_errors.h"

FMOD::System* audioSystem = nullptr;;

AudioSystem::AudioSystem() {
    FMOD_RESULT result;
    result = FMOD::System_Create(&audioSystem);

    if (result != FMOD_OK) {
        Logger::Error("FMOD system creation failed: " + std::string(FMOD_ErrorString(result)));
    }
    else {
        result = audioSystem->init(32, FMOD_INIT_NORMAL, nullptr);
        if (result != FMOD_OK) {
            Logger::Error("FMOD system initialization failed: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

AudioSystem::~AudioSystem() {
}

void AudioSystem::Update(float deltaTime) {
    audioSystem->update();
}

void AudioSystem::PlayPause(uint32_t entityID) {
    AudioComponent* audioComponent = ComponentStore::GetInstance().getComponent<AudioComponent>(entityID);

    if (!audioComponent) {
        Logger::Error("AudioComponent not found for entityID: " + std::to_string(entityID));
        return;
    }

    FMOD_RESULT result;
    bool isPlaying = false;

    if (audioComponent->channel) {
        result = audioComponent->channel->isPlaying(&isPlaying);

        if (result != FMOD_OK) {
            const char* errorMessage = FMOD_ErrorString(result);
            Logger::Error("Error checking playback state: " + std::string(errorMessage));
            return;
        }

        if (isPlaying) {
            result = audioComponent->channel->setPaused(true);
            if (result != FMOD_OK) {
                const char* errorMessage = FMOD_ErrorString(result);
                Logger::Error("Error pausing audio: " + std::string(errorMessage));
            }
        } else {
            result = audioComponent->channel->setPaused(false);
            if (result != FMOD_OK) {
                const char* errorMessage = FMOD_ErrorString(result);
                Logger::Error("Error resuming audio playback: " + std::string(errorMessage));
            }
        }
    }
}

const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {
    if (audioSystem) {
        audioSystem->release();
        audioSystem = nullptr;
    }
}
