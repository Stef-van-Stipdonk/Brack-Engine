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
        std::vector<AudioComponent*> audioComponents = ComponentStore::GetInstance().getComponentsForEntityId<AudioComponent>(entity);
        for(auto audioComponent : audioComponents){
            // Access the playbackStateMap through the AudioWrapper
            const auto& playbackStateMap = audioWrapper->GetPlaybackStateMap();
            auto playbackStateIterator = playbackStateMap.find(audioComponent->channel);

            // Check if the sound needs to be uploaded (formerly StartSound)
            if (playbackStateIterator == playbackStateMap.end() || !playbackStateIterator->second) {
                // Check if the file exists
                std::ifstream file(audioComponent->audioPath);
                if (!file.good()) {
                    Logger::Error("Audio file not found at path: " + audioComponent->audioPath);
                    continue;
                }

                //Check if a non-soundtrack sound is being added to the soundtrackchannel
                if(audioComponent->channel == audioWrapper->GetSoundTrackChannelID() && !audioComponent->isSoundTrack)
                    Logger::Error("Cannot place non-soundtrack sounds on the soundtrack channel: Soundtrack Channel = " +  std::to_string(audioWrapper->GetSoundTrackChannelID()));

                audioWrapper->UploadSound(*audioComponent);
            }

            if(audioWrapper->GetVolume(*audioComponent) != audioComponent->volume){
                audioWrapper->SetVolume(*audioComponent, audioComponent->volume);
            }
            if(audioWrapper->GetLooping(*audioComponent) != audioComponent->isLooping){
                audioWrapper->SetLooping(*audioComponent, audioComponent->isLooping);
            }

            // Check if the sound is playing or not
            bool isPlaying = playbackStateIterator != playbackStateMap.end() && playbackStateIterator->second;

            if (audioComponent->isPlaying && !isPlaying) {
                // If the sound is supposed to play, and it's not playing, start it
                audioWrapper->ResumeSound(*audioComponent);
                audioWrapper->SetPlaybackState(audioComponent->channel, true);
            } else if (!audioComponent->isPlaying && isPlaying) {
                // If the sound is not supposed to, and it's playing, pause it
                audioWrapper->PauseSound(*audioComponent);
                audioWrapper->SetPlaybackState(audioComponent->channel, false);
            }

            Logger::Debug("Channel: " + std::to_string(audioComponent->channel) + ", isPlaying: " + std::to_string(isPlaying));
        }
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
