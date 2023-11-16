//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TEXTCOMPONENT_HPP
#define BRACK_ENGINE_TEXTCOMPONENT_HPP

#include <string>
#include <memory>
#include "Helpers/Color.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include "Components/Archetypes/RenderArchetype.hpp"


struct TextComponent : public RenderArchetype {
    explicit TextComponent() : RenderArchetype() {}

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<TextComponent>(*this);
    }

    TextComponent(const TextComponent &other) : RenderArchetype(other) {
        text = other.text;
        fontPath = other.fontPath;
        fontSize = other.fontSize;

        if (other.color != nullptr)
            color = std::make_unique<Color>(*other.color);
    }


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::string text = "";
    std::string fontPath = "";
    int fontSize = 10;
    std::unique_ptr<Color> color = std::make_unique<Color>(0, 0, 0, 255);
};

#endif //BRACK_ENGINE_TEXTCOMPONENT_HPP
