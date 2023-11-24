//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"

AudioSystem::AudioSystem() : audioWrapper(new AudioWrapper()) {
}

AudioSystem::~AudioSystem() {
}

void AudioSystem::update(float deltaTime) {
    auto audiocomponents = ComponentStore::GetInstance().getAllComponentsOfType<AudioArchetype>();
    for(auto audioComponent : audiocomponents){
        if(audioComponent->isSoundTrack && audioComponent->startPlaying && !audioComponent->pauseSound){
            audioComponent->startPlaying = false;
            audioWrapper->playSoundTrack(*audioComponent);
        }else if(!audioComponent->isSoundTrack && audioComponent->startPlaying && !audioComponent->pauseSound){
            audioComponent->startPlaying = false;
            audioWrapper->playSoundEffect(*audioComponent);
        }

        if(audioComponent->pauseSound && audioComponent->startPlaying){
            audioComponent->pauseSound = false;
            audioComponent->startPlaying = false;
            audioWrapper->resumeSound(*audioComponent);
        }
        else if (audioComponent->pauseSound){
            audioWrapper->pauseSound(*audioComponent);
        }
    }
}

const std::string AudioSystem::getName() const {
    return "AudioSystem";
}

void AudioSystem::cleanUp() {
    auto entities = ComponentStore::GetInstance().getEntitiesWithComponent<AudioArchetype>();
    for(auto entity : entities){
        auto audioComponent = ComponentStore::GetInstance().tryGetComponent<AudioArchetype>(entity);
            audioComponent.startPlaying = false;
    }
    audioWrapper->cleanUp();
}
