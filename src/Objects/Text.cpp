//
// Created by jesse on 31/10/2023.
//

#include <Components/TextComponent.hpp>
#include "Objects/Text.hpp"
#include "../ConfigSingleton.hpp"

Text::Text(std::string text, int fontSize, Color color, std::string fontPath) {
    std::unique_ptr<TextComponent> textComponent = std::make_unique<TextComponent>();
    textComponent->text = text;
    textComponent->fontSize = fontSize;
    textComponent->color = std::make_unique<Color>(color);
    textComponent->fontPath = fontPath;
    AddComponent(std::move(textComponent));
}

Text::Text(std::string text, int fontSize, Color color) : Text(text, fontSize, color, ConfigSingleton::GetInstance().GetBaseAssetPath() + "Fonts/Arial.ttf") {}
Text::Text(std::string text, int fontSize) : Text(text, fontSize, Color(0,0,0,255)) {}
Text::Text(std::string text) : Text(text, 24) {}