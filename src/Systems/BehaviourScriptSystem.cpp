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
    auto notStartedBehaviourScripts = ComponentStore::GetInstance().notStartedBehaviourScripts;
    std::sort(behaviorScripts.begin(), behaviorScripts.end(), compareByPriority);


    for (auto script: behaviorScripts) {
        auto &scriptref = *script;
        auto it = std::find_if(
                notStartedBehaviourScripts.begin(),
                notStartedBehaviourScripts.end(),
                [&](const std::reference_wrapper<BehaviourScript> &ref) {
                    return &ref.get() == script;
                }
        );
        if (it != notStartedBehaviourScripts.end()) {
            script->onStart();
            ComponentStore::GetInstance().removeBehaviourScript(scriptref);
        }
        script->onUpdate(deltaTime);
    }
}


const std::string BehaviourScriptSystem::getName() const {
    return "BehaviourScriptSystem";
}

void BehaviourScriptSystem::cleanUp() {

}


