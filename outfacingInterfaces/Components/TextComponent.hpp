//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TEXTCOMPONENT_HPP
#define BRACK_ENGINE_TEXTCOMPONENT_HPP

#include <string>
#include <memory>
#include "Helpers/Color.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include "UIComponent.hpp"

struct TextComponent : public UIComponent {
    explicit TextComponent() : UIComponent() {}

    TextComponent(const TextComponent &other) : UIComponent(other) {
        text = other.text;
        fontPath = other.fontPath;
        fontSize = other.fontSize;
        color = std::make_unique<Color>(*other.color);
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::string text, fontPath;
    int fontSize;
    std::unique_ptr<Color> color;
};

#endif //BRACK_ENGINE_TEXTCOMPONENT_HPP
