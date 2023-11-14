//
// Created by jesse on 31/10/2023.
//

#include <Components/RectangleComponent.hpp>
#include <Components/TextComponent.hpp>
#include <Components/ClickableComponent.hpp>
#include <Components/BoxCollisionComponent.hpp>
#include <utility>
#include "Objects/Button.hpp"

Button::Button(const Vector2& size, const std::string& text) : UIObject() {
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

void Button::SetTextColor(const Color& color) {
    if (entityID == 0) {
        GetComponent<TextComponent>()->color = std::make_unique<Color>(color);
    } else
        ComponentStore::GetInstance().getComponent<TextComponent>(entityID)->color = std::make_unique<Color>(color);
}

void Button::SetFontPath(const std::string& path) {
    if (entityID == 0) {
        GetComponent<TextComponent>()->fontPath = path;
    } else
        ComponentStore::GetInstance().getComponent<TextComponent>(entityID)->fontPath = path;
}

void Button::SetFontSize(int fontSize) {
    if (entityID == 0) {
        GetComponent<TextComponent>()->fontSize = fontSize;
    } else
        ComponentStore::GetInstance().getComponent<TextComponent>(entityID)->fontSize = fontSize;
}

void Button::SetText(const std::string& string) {
    if (entityID == 0) {
        GetComponent<TextComponent>()->text = string;
    } else
        ComponentStore::GetInstance().getComponent<TextComponent>(entityID)->text = string;
}

void Button::SetFill(const Color& color) {
    if (entityID == 0) {
        GetComponent<RectangleComponent>()->fill = std::make_unique<Color>(color);
    } else
        ComponentStore::GetInstance().getComponent<RectangleComponent>(entityID)->fill = std::make_unique<Color>(color);
}

void Button::SetClickEvent(std::function<void()> func) {
    GetComponent<ClickableComponent>()->OnClick = std::move(func);
}

void Button::SetBorderWidth(int borderWidth) {
    if (entityID == 0) {
        GetComponent<RectangleComponent>()->borderWidth = borderWidth;
    } else
        ComponentStore::GetInstance().getComponent<RectangleComponent>(entityID)->borderWidth = borderWidth;
}

void Button::SetBorderColor(const Color& color) {
    if (entityID == 0) {
        GetComponent<RectangleComponent>()->borderColor = std::make_unique<Color>(color);
    } else
        ComponentStore::GetInstance().getComponent<RectangleComponent>(entityID)->borderColor = std::make_unique<Color>(color);
}

bool Button::IsDisabled() const {
    return GetComponent<ClickableComponent>()->disabled;
}

void Button::SetDisabled(bool disabled) {
    if (entityID == 0) {
        GetComponent<ClickableComponent>()->disabled = disabled;
    } else
        ComponentStore::GetInstance().getComponent<ClickableComponent>(entityID)->disabled = disabled;
}
