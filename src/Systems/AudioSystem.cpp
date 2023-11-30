//
// Created by jesse on 31/10/2023.
//

#include "AudioSystem.hpp"
#include "../outfacingInterfaces/Entity.hpp"

AudioSystem::AudioSystem() {

}

AudioSystem::~AudioSystem() {

}

void AudioSystem::update(milliseconds deltaTime) {
}

void AudioSystem::PlayPause(entity entityId) {

}

const std::string AudioSystem::getName() const {
    return "AudioSystem";
}

void AudioSystem::cleanUp() {

}

AudioSystem::AudioSystem(const AudioSystem &other) {
    audioWrapper = std::make_unique<AudioWrapper>(*other.audioWrapper);
}