//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"
#include "../includes/EntityManager.hpp"
#include <fstream>
#include <Components/Archetypes/AudioArchetype.hpp>

AudioSystem::AudioSystem() : audioWrapper(new AudioWrapper()) {
}

AudioSystem::~AudioSystem() {
}

void AudioSystem::update(float deltaTime) {
    auto audiocomponents = ComponentStore::GetInstance().getAllComponentsOfType<AudioArchetype>();
    for(auto audioComponent : audiocomponents){
        if(audioComponent->startPlaying){
            audioComponent->startPlaying = false;
            audioWrapper->playSound(*audioComponent);
        }
        if(audioComponent->pauseSound){
            audioWrapper->pauseSound(*audioComponent);
        }
        else{
            audioWrapper->resumeSound(*audioComponent);
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
