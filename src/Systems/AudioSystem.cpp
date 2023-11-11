//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"
#include "../includes/EntityManager.hpp"
#include <fstream>
#include <Components/SoundTrackComponent.hpp>
#include <Components/SoundEffectComponent.hpp>

AudioSystem::AudioSystem() : audioWrapper(new AudioWrapper()) {
}

AudioSystem::~AudioSystem() {
}

void AudioSystem::Update(float deltaTime) {
    auto entities = ComponentStore::GetInstance().getEntitiesWithComponent<AudioComponent>();

    for (auto entity : entities) {
        const auto& audioComponents = ComponentStore::GetInstance().GetComponents<AudioComponent>(entity);
        for (const auto& audioComponent : audioComponents) {
            // Access the playbackStateMap through the AudioWrapper
            const auto &playbackStateMap = audioWrapper->GetPlaybackStateMap();
            auto playbackStateIterator = playbackStateMap.find(audioComponent->GetChannel());

            // Check if the sound needs to be uploaded (formerly StartSound)
            if (playbackStateIterator == playbackStateMap.end() || !playbackStateIterator->second) {
                // Check if the file exists
                std::ifstream file(audioComponent->audioPath);
                if (!file.good()) {
                    Logger::Error("Audio file not found at path: " + audioComponent->audioPath);
                    continue;
                }

                audioWrapper->UploadSound(*audioComponent);
            }

            if (audioWrapper->GetVolume(*audioComponent) != audioComponent->volume) {
                audioWrapper->SetVolume(*audioComponent, audioComponent->volume);
            }
            if (audioWrapper->GetLooping(*audioComponent) != audioComponent->isLooping) {
                audioWrapper->SetLooping(*audioComponent, audioComponent->isLooping);
            }

            // Check if the sound is playing or not
            bool isPlaying = playbackStateIterator != playbackStateMap.end() && playbackStateIterator->second;

            if (audioComponent->isPlaying && !isPlaying) {
                // If the sound is supposed to play, and it's not playing, start it
                audioWrapper->ResumeSound(*audioComponent);
                audioWrapper->SetPlaybackState(audioComponent->GetChannel(), true);
            } else if (!audioComponent->isPlaying && isPlaying) {
                // If the sound is not supposed to, and it's playing, pause it
                audioWrapper->PauseSound(*audioComponent);
                audioWrapper->SetPlaybackState(audioComponent->GetChannel(), false);
            }

            Logger::Debug("Channel: " + std::to_string(audioComponent->GetChannel()) + ", isPlaying: " +
                          std::to_string(isPlaying));
        }
    }
}

const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {
    auto entities = ComponentStore::GetInstance().getEntitiesWithComponent<AudioComponent>();

    for (auto entity : entities) {
        auto audioComponents = ComponentStore::GetInstance().GetComponents<AudioComponent>(entity);
        for (auto audioComponent : audioComponents) {
            audioWrapper->StopSound(*audioComponent);
        }
    }
    audioWrapper->CleanUp();
}
