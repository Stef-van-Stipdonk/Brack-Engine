//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"
#include "../includes/EntityManager.hpp"
#include <fstream>

AudioSystem::AudioSystem() : audioWrapper(new AudioWrapper()) {
}

AudioSystem::~AudioSystem() {
}

void AudioSystem::Update(float deltaTime) {
    auto entities = ComponentStore::GetInstance().getEntitiesWithComponent<AudioComponent>();
    for (auto entity : entities) {
        auto audioComponent = ComponentStore::GetInstance().getComponent<AudioComponent>(entity);

        // Check if the file exists
        std::ifstream file(audioComponent->audioPath);
        if (!file.good()) {
            Logger::Info("Audio file not found at path: " + audioComponent->audioPath);
            continue;
        }
        // Access the playbackStateMap through the AudioWrapper
        const auto& playbackStateMap = audioWrapper->GetPlaybackStateMap();

        auto playbackStateIt = playbackStateMap.find(audioComponent->entityID);

        // Check if the sound needs to be uploaded (formerly StartSound)
        if (playbackStateIt == playbackStateMap.end() || !playbackStateIt->second) {
            audioWrapper->UploadSound(*audioComponent);

            audioWrapper->SetPlaybackState(audioComponent->entityID, false);
        }

        // Check if the sound is playing or not
        bool isPlaying = playbackStateIt != playbackStateMap.end() && playbackStateIt->second;

        if (audioComponent->isPlaying && !isPlaying) {
            // If the sound is supposed to play, and it's not playing, start it
            audioWrapper->ResumeSound(*audioComponent);
            audioWrapper->SetPlaybackState(audioComponent->entityID, true);
        } else if (!audioComponent->isPlaying && isPlaying) {
            // If the sound is not supposed to, and it's playing, pause it
            audioWrapper->PauseSound(*audioComponent);
            audioWrapper->SetPlaybackState(audioComponent->entityID, false);
        }

        audioWrapper->SetLooping(*audioComponent, audioComponent->isLooping);
        audioWrapper->SetVolume(*audioComponent, audioComponent->volume);
    }
}

const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {
    auto entities = ComponentStore::GetInstance().getEntitiesWithComponent<AudioComponent>();

    for (auto entity : entities) {
        auto audioComponent = ComponentStore::GetInstance().getComponent<AudioComponent>(entity);
        audioWrapper->StopSound(*audioComponent);
    }
    audioWrapper->CleanUp();
}
