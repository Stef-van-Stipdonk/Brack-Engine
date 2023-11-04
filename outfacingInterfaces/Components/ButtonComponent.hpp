//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BUTTONCOMPONENT_HPP
#define BRACK_ENGINE_BUTTONCOMPONENT_HPP

#include <functional>
#include "UIComponent.hpp"

struct ButtonComponent : public UIComponent {
    explicit ButtonComponent(uint32_t entityId) : UIComponent(entityId) {}

    bool interactable;
    std::function<void()> OnClick;
};

#endif //BRACK_ENGINE_BUTTONCOMPONENT_HPP
