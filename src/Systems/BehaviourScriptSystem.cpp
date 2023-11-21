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

void BehaviourScriptSystem::update(float deltaTime) {
    auto entities = ComponentStore::GetInstance().getAllComponentsOfType<BehaviourScript>();
    for (auto entity: entities) {
//        auto& behaviourScriptComponent = ComponentStore::GetInstance().tryGetComponent<BehaviourScript>(entity);
        entity->OnUpdate(deltaTime);
    }
}

const std::string BehaviourScriptSystem::getName() const {
    return "BehaviourScriptSystem";
}

void BehaviourScriptSystem::cleanUp() {

}
