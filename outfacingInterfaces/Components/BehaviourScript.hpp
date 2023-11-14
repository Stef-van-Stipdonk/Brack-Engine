//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BEHAVIOURSCRIPT_HPP
#define BRACK_ENGINE_BEHAVIOURSCRIPT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include <functional>

struct BehaviourScript : public IComponent {
    explicit BehaviourScript() : IComponent() {}

    ~BehaviourScript() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
        OnStart();
    }

    virtual void OnStart() {};

    virtual void OnUpdate(float deltaTime) {};
};


#endif //BRACK_ENGINE_BEHAVIOURSCRIPT_HPP
