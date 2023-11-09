//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_UICOMPONENT_HPP
#define BRACK_ENGINE_UICOMPONENT_HPP

#include <memory>
#include "IComponent.hpp"
#include "Helpers/Vector2.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct UIComponent : public IComponent {
    explicit UIComponent() : IComponent() {}

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<UIComponent>(this);
    }

    std::unique_ptr<Vector2> size;
};

#endif //BRACK_ENGINE_UICOMPONENT_HPP
