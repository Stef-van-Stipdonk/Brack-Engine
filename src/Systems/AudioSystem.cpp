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

void AudioSystem::StartSound() {
    if (audioWrapper) {
        audioWrapper->StartSound();
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::StopSoundChannel() {
    if (audioWrapper) {
        audioWrapper->StopSoundChannel();
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::ResumeChannel(int channelID) {
    if (audioWrapper) {
        audioWrapper->ResumeChannel(channelID);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::PauseChannel(int channelID) {
    if (audioWrapper) {
        audioWrapper->PauseChannel(channelID);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}


void AudioSystem::SetVolume(int channelID, float volume) {
    if (audioWrapper) {
        audioWrapper->SetVolume(channelID, volume);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::SetLooping(int channelID, bool loop) {
    if (audioWrapper) {
        audioWrapper->SetLooping(channelID, loop);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}


const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {
}
