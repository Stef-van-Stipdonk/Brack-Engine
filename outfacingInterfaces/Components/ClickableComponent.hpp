//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BUTTONCOMPONENT_HPP
#define BRACK_ENGINE_BUTTONCOMPONENT_HPP

#include <functional>
#include <utility>
#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct ClickableComponent : public IComponent {
    ClickableComponent() : IComponent() {}
    
    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<ClickableComponent>(*this);

    }

    ~ClickableComponent() override = default;

    ClickableComponent(const ClickableComponent &other) : IComponent(other) {
        OnClick = other.OnClick;
    }

    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    bool disabled = false;
    std::function<void()> OnClick;
};

#endif //BRACK_ENGINE_BUTTONCOMPONENT_HPP
