//
// Created by jesse on 31/10/2023.
//

#include <Components/TextComponent.hpp>
#include <Components/RectangleComponent.hpp>
#include <utility>
#include "Objects/Text.hpp"
#include "../ConfigSingleton.hpp"

Text::Text(const std::string& text) : UIObject() {
    auto* textComponent = new TextComponent();
    textComponent->text = text;
    AddComponent(textComponent);
}

void Text::SetFontSize(int fontSize) {
    if (entityID == 0) {
        GetComponent<TextComponent>()->fontSize = fontSize;
    } else
        ComponentStore::GetInstance().getComponent<TextComponent>(entityID)->fontSize = fontSize;
}

void Text::SetColor(const Color &color) {
    if (entityID == 0) {
        GetComponent<TextComponent>()->color = std::make_unique<Color>(color);
    } else
        ComponentStore::GetInstance().getComponent<TextComponent>(entityID)->color = std::make_unique<Color>(color);
}

void Text::SetFontPath(const std::string &font) {
    if (entityID == 0) {
        GetComponent<TextComponent>()->fontPath = font;
    } else
        ComponentStore::GetInstance().getComponent<TextComponent>(entityID)->fontPath = font;
}

void Text::SetText(const std::string &text) {
    if (entityID == 0) {
        GetComponent<TextComponent>()->text = text;
    } else
        ComponentStore::GetInstance().getComponent<TextComponent>(entityID)->text = text;
}
