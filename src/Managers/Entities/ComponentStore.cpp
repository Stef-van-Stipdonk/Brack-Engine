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

void ComponentStore::removeBehaviourScript(BehaviourScript &behaviourScript) {
    auto it = std::find_if(
            notStartedBehaviourScripts.begin(),
            notStartedBehaviourScripts.end(),
            [&](const std::reference_wrapper<BehaviourScript> &ref) {
                return &ref.get() == &behaviourScript;
            }
    );
    if (it != notStartedBehaviourScripts.end()) {
        notStartedBehaviourScripts.erase(it);
    }
}