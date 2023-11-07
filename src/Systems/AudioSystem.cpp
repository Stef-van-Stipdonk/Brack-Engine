//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"
#include "fmod.hpp"
#include "../includes/ComponentStore.hpp"

AudioSystem::AudioSystem() {
}

AudioSystem::~AudioSystem() {
}

void AudioSystem::Update(float deltaTime) {
}

void AudioSystem::PlayAudio(uint32_t entityID, const std::string& audioFilePath) {
    if (audioWrapper) {
        audioWrapper->PlayAudio(entityID, audioFilePath);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::StopAudio(uint32_t entityID) {
    if (audioWrapper) {
        audioWrapper->StopAudio(entityID);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::PlayPause(uint32_t entityID) {
    if (audioWrapper) {
        audioWrapper->PlayPause(entityID);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::SetVolume(uint32_t entityID, float volume) {
    if (audioWrapper) {
        audioWrapper->SetVolume(entityID, volume);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::SetLooping(uint32_t entityID, bool loop) {
    if (audioWrapper) {
        audioWrapper->SetLooping(entityID, loop);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}


const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {
}
