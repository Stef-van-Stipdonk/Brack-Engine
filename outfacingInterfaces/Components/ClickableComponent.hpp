//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BUTTONCOMPONENT_HPP
#define BRACK_ENGINE_BUTTONCOMPONENT_HPP

#include <functional>
#include <utility>
#include "UIComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct ClickableComponent : public UIComponent {
    explicit ClickableComponent(std::function<void()> func) : UIComponent() {
        OnClick = std::move(func);
    }


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<ClickableComponent>(this);
    }

    bool disabled;
    std::function<void()> OnClick;
};

#endif //BRACK_ENGINE_BUTTONCOMPONENT_HPP
