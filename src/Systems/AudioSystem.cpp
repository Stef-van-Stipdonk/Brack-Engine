//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"

AudioSystem::AudioSystem() {

}

AudioSystem::~AudioSystem() {

}

void AudioSystem::Update(float deltaTime) {
    auto fak = ComponentStore::GetInstance().getAllComponentsOfType<AudioComponent>();
}

void AudioSystem::PlayPause(uint32_t entityID) {

}

const std::string AudioSystem::GetName() const {
    return "AudioSystem";
}

void AudioSystem::CleanUp() {

}
