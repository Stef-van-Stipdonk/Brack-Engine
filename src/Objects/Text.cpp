//
// Created by jesse on 31/10/2023.
//

#include <Components/TextComponent.hpp>
#include "Objects/Text.hpp"
#include "../ConfigSingleton.hpp"

Text::Text(std::string text, int fontSize, std::unique_ptr<Color> color, std::string fontPath) {
    std::unique_ptr<TextComponent> textComponent = std::make_unique<TextComponent>();
    textComponent->text = text;
    textComponent->fontSize = fontSize;
    textComponent->color = std::move(color);
    textComponent->fontPath = fontPath;
    AddComponent(textComponent);
}
Text::Text(std::string text, int fontSize, std::unique_ptr<Color> color) : Text(text, fontSize, std::move(color), ConfigSingleton::GetInstance().GetBaseAssetPath() + "Fonts/Arial.ttf") {}
Text::Text(std::string text, int fontSize) : Text(text, fontSize, std::make_unique<Color>(0,0,0,255)) {}
Text::Text(std::string text) : Text(text, 24) {}

void Text::SetText(const std::string text) {

}

std::string Text::GetText() const {
    return std::string();
}

void Text::SetFontPath(const std::string font) {

}

std::string Text::GetFont() const {
    return std::string();
}

void Text::SetFontSize(const int fontSize) {

}

int Text::GetFontSize() const {
    return 0;
}

void Text::SetColor(const Color &color) {

}

Color &Text::GetColor() const {
    return *new Color();
}
