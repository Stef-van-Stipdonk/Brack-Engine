//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BEHAVIOURSCRIPT_HPP
#define BRACK_ENGINE_BEHAVIOURSCRIPT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include <functional>

struct BehaviourScript : public IComponent {
    explicit BehaviourScript() = default;

    ~BehaviourScript() override = default;

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<BehaviourScript>(*this);
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
        OnStart();
    }

    BehaviourScript(const BehaviourScript &other) : IComponent(other) {}

    virtual void OnStart() {};

    virtual void OnUpdate(float deltaTime) {};

    template<typename T>
    typename std::enable_if_t<std::is_base_of<IComponent, T>::value>::type
    tryGetComponent() {
        return ComponentStore::GetInstance().tryGetComponent<T>(entityID);
    }
};


#endif //BRACK_ENGINE_BEHAVIOURSCRIPT_HPP
