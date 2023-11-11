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
    //This should work using audiocomponent, but I cannot seem to get getentitieswithcomponent to work with derived components.
    auto temporarySoundEffectEntities = ComponentStore::GetInstance().getEntitiesWithComponent<SoundEffectComponent>();
    for (auto entity : temporarySoundEffectEntities) {
        const auto& audioComponents = ComponentStore::GetInstance().GetComponents<SoundEffectComponent>(entity);
        for (const auto& audioComponent : audioComponents) {
            if(!audioWrapper->IsInitialized(*audioComponent)){
                if(audioWrapper->IsValidAudioPath(*audioComponent)){
                    audioWrapper->UploadSound(*audioComponent);
                }
            }
            
            if (audioWrapper->GetVolume(*audioComponent) != audioComponent->volume) {
                audioWrapper->SetVolume(*audioComponent, audioComponent->volume);
            }
            if (audioWrapper->GetLooping(*audioComponent) != audioComponent->isLooping) {
                audioWrapper->SetLooping(*audioComponent, audioComponent->isLooping);
            }
            if(audioWrapper->HasSoundFinished(*audioComponent)){
                audioComponent->isPlaying = false;
            }
        }
    }
}

void AudioSystem::PlaySound(AudioComponent& audioComponent){
    audioWrapper->PlaySound(audioComponent);
    audioComponent.isPlaying = true;
}

void AudioSystem::PauseSound(AudioComponent& audioComponent){
    audioWrapper->PauseSound(audioComponent);
    audioComponent.isPlaying = false;
}

void AudioSystem::StopSound(AudioComponent& audioComponent){
    audioWrapper->StopSound(audioComponent);
    audioComponent.isPlaying = false;
}

const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {
    auto entities = ComponentStore::GetInstance().getEntitiesWithComponent<AudioComponent>();

    for (auto entity : entities) {
        auto audioComponents = ComponentStore::GetInstance().GetComponents<AudioComponent>(entity);
        for (auto audioComponent : audioComponents) {
            audioWrapper->RemoveSound(*audioComponent);
            audioComponent->isPlaying = false;
        }
    }
    audioWrapper->CleanUp();
}
