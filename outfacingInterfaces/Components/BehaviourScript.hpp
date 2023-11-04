//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BEHAVIOURSCRIPT_HPP
#define BRACK_ENGINE_BEHAVIOURSCRIPT_HPP

#include "IComponent.hpp"
#include <functional>

struct BehaviourScript : public IComponent {

    explicit BehaviourScript(uint32_t entityId) : IComponent(entityId) {}

    ~BehaviourScript() override = default;

    std::function<void()> OnStart;
    std::function<void(float)> OnUpdate;
};


#endif //BRACK_ENGINE_BEHAVIOURSCRIPT_HPP
