//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BUTTONCOMPONENT_HPP
#define BRACK_ENGINE_BUTTONCOMPONENT_HPP

#include <functional>
#include "UIComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct ButtonComponent : public UIComponent {
    explicit ButtonComponent() : UIComponent() {}


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<ButtonComponent>(this);
    }

    bool interactable;
    std::function<void()> OnClick;
};

#endif //BRACK_ENGINE_BUTTONCOMPONENT_HPP
