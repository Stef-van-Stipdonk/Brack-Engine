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

bool compareByPriority(const BehaviourScript *obj1, const BehaviourScript *obj2) {
    return obj1->getPriority() < obj2->getPriority();
}


void BehaviourScriptSystem::update(milliseconds deltaTime) {
    auto behaviorScripts = ComponentStore::GetInstance().getAllComponentsOfType<BehaviourScript>();
    std::sort(behaviorScripts.begin(), behaviorScripts.end(), compareByPriority);


    for (auto script: behaviorScripts) {
        script->onUpdate(deltaTime);
    }
}


const std::string BehaviourScriptSystem::getName() const {
    return "BehaviourScriptSystem";
}

void BehaviourScriptSystem::cleanUp() {

}


