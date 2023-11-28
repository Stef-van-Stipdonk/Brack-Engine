//
// Created by jesse on 31/10/2023.
//

#include <Components/BehaviourScript.hpp>
#include <Components/Archetypes/AudioArchetype.hpp>
#include "BehaviourScriptSystem.hpp"

BehaviourScriptSystem::BehaviourScriptSystem() {

}

BehaviourScriptSystem::~BehaviourScriptSystem() {

}

void BehaviourScriptSystem::update(int deltaTime) {
    auto behaviorScripts = ComponentStore::GetInstance().getAllComponentsOfType<BehaviourScript>();
    for (auto script: behaviorScripts) {
        script->onUpdate(deltaTime);
    }
}

const std::string BehaviourScriptSystem::getName() const {
    return "BehaviourScriptSystem";
}

void BehaviourScriptSystem::cleanUp() {

}


