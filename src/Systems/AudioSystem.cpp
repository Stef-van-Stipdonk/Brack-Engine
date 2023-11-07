//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"

AudioSystem::AudioSystem() : audioWrapper(new AudioWrapper()) {
}

AudioSystem::~AudioSystem() {
}

void AudioSystem::Update(float deltaTime) {
}

void AudioSystem::StartSound(AudioComponent &audioComponent) {
    if (audioWrapper) {
        audioWrapper->StartSound(audioComponent);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::StopSound(AudioComponent &audioComponent) {
    if (audioWrapper) {
        audioWrapper->StopSound(audioComponent);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::ResumeSound(AudioComponent &audioComponent) {
    if (audioWrapper) {
        audioWrapper->ResumeSound(audioComponent);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::PauseSound(AudioComponent &audioComponent) {
    if (audioWrapper) {
        audioWrapper->PauseSound(audioComponent);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}


void AudioSystem::SetVolume(AudioComponent &audioComponent, float volume) {
    if (audioWrapper) {
        audioWrapper->SetVolume(audioComponent, volume);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}

void AudioSystem::SetLooping(AudioComponent &audioComponent, bool loop) {
    if (audioWrapper) {
        audioWrapper->SetLooping(audioComponent, loop);
    } else {
        Logger::Error("AudioSystem is not initialized.");
    }
}


const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {
    audioWrapper->CleanUp()
}
