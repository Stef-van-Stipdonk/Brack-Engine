//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"
#include "../includes/EntityManager.hpp"
#include <fstream>
#include <Components/AudioComponent.hpp>

AudioSystem::AudioSystem() : audioWrapper(new AudioWrapper()) {
}

AudioSystem::~AudioSystem() {
}

void AudioSystem::Update(float deltaTime) {
    auto archetypes = ComponentStore::GetInstance().getAllComponentsOfType<AudioComponent>();
    for(auto audioComponent : archetypes){
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
    auto entities = ComponentStore::GetInstance().getEntitiesWithComponent<AudioComponent>();
    for(auto entity : entities){
        auto audioComponent = ComponentStore::GetInstance().tryGetComponent<AudioComponent>(entity);
            audioComponent.startPlaying = false;
    }
    audioWrapper->CleanUp();
}
