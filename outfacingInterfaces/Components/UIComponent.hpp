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

    UIComponent(const UIComponent &other) : IComponent(other) {
        if(other.size != nullptr)
            size = std::make_unique<Vector2>(*other.size);
    }

    virtual std::unique_ptr<IComponent> clone() const override{
        return std::make_unique<UIComponent>(*this);
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::unique_ptr<Vector2> size;
};

#endif //BRACK_ENGINE_UICOMPONENT_HPP
