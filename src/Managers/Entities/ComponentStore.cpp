//
// Created by jesse on 17/11/2023.
//

#include "../../includes/ComponentStore.hpp"
#include "../../../outfacingInterfaces//Components/BehaviourScript.hpp"

ComponentStore ComponentStore::instance;

ComponentStore &ComponentStore::GetInstance() {
    return instance;
}

void ComponentStore::checkBehaviourScript(std::unique_ptr<IComponent> &component) {
    auto behaviourScript = dynamic_cast<BehaviourScript *>(component.get());
    if (behaviourScript != nullptr) {
        notStartedBehaviourScripts.push_back(std::ref(*behaviourScript));
    }

}