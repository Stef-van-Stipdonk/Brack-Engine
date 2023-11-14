//
// Created by jesse on 31/10/2023.
//

#include <Components/RectangleComponent.hpp>
#include <Components/TextComponent.hpp>
#include <Components/ClickableComponent.hpp>
#include <Components/BoxCollisionComponent.hpp>
#include <utility>
#include "Objects/Button.hpp"

Button::Button(Vector2 size, std::string text) {
    auto* textComponent = new TextComponent();
    textComponent->text = std::move(text);

    auto* rectangleComponent = new RectangleComponent(size);

    auto* boxCollisionComponent = new BoxCollisionComponent(size);

    auto* clickableComponent = new ClickableComponent();

    AddComponent(boxCollisionComponent);
    AddComponent(clickableComponent);
    AddComponent(rectangleComponent);
    AddComponent(textComponent);
}

void Button::SetTextColor(Color color) {
    GetComponent<TextComponent>()->color = std::make_unique<Color>(color);
}

void Button::SetFontPath(std::string path) {
    GetComponent<TextComponent>()->fontPath = std::move(path);
}

void Button::SetFontSize(int fontSize) {
    GetComponent<TextComponent>()->fontSize = fontSize;
}

void Button::SetText(std::string string) {
    GetComponent<TextComponent>()->text = std::move(string);
}

void Button::SetFill(Color color) {
    GetComponent<RectangleComponent>()->fill = std::make_unique<Color>(color);
}

void Button::SetClickEvent(std::function<void()> func) {
    GetComponent<ClickableComponent>()->OnClick = std::move(func);
}

void Button::SetBorderWidth(int borderWidth) {
    GetComponent<RectangleComponent>()->borderWidth = borderWidth;
}

void Button::SetBorderColor(Color color) {
    GetComponent<RectangleComponent>()->borderColor = std::make_unique<Color>(color);
}

bool Button::IsDisabled() const {
    return GetComponent<ClickableComponent>()->disabled;
}

void Button::SetDisabled(const bool disabled) {
    GetComponent<ClickableComponent>()->disabled = disabled;
}
