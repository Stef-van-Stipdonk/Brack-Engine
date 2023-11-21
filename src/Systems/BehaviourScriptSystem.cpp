//
// Created by jesse on 31/10/2023.
//

#include <Components/BehaviourScript.hpp>
#include "BehaviourScriptSystem.hpp"

BehaviourScriptSystem::BehaviourScriptSystem() {

}

BehaviourScriptSystem::~BehaviourScriptSystem() {

}

void BehaviourScriptSystem::Update(float deltaTime) {
    auto entities = ComponentStore::GetInstance().getAllComponentsOfType<BehaviourScript>();
    for (auto entity: entities) {
        entity->onUpdate(deltaTime);
    }
}

const std::string BehaviourScriptSystem::GetName() const {
    return "BehaviourScriptSystem";
}

void BehaviourScriptSystem::CleanUp() {

}
