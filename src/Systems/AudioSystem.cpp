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

void AudioSystem::Update(float deltaTime) {
    auto audiocomponents = ComponentStore::GetInstance().getAllComponentsOfType<AudioArchetype>();
    for(auto audioComponent : audiocomponents){
        if(audioComponent->startPlaying){
            audioComponent->startPlaying = false;
            audioWrapper->PlaySound(*audioComponent);
        }
    }
}

const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {
    auto entities = ComponentStore::GetInstance().getEntitiesWithComponent<AudioArchetype>();
    for(auto entity : entities){
        auto audioComponent = ComponentStore::GetInstance().tryGetComponent<AudioArchetype>(entity);
            audioComponent.startPlaying = false;
    }
    audioWrapper->CleanUp();
}
