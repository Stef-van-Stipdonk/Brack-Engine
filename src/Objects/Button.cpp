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
    auto textComponent = std::make_unique<TextComponent>();
    textComponent->text = std::move(text);

    auto rectangleComponent = std::make_unique<RectangleComponent>(size);

    auto boxCollisionComponent = std::make_unique<BoxCollisionComponent>(size);

    auto clickableComponent = std::make_unique<ClickableComponent>();

    AddComponent(std::move(boxCollisionComponent));
    AddComponent(std::move(clickableComponent));
    AddComponent(std::move(rectangleComponent));
    AddComponent(std::move(textComponent));
}

void Button::SetTextColor(const Color& color) {
    if (entityID == 0) {
        TryGetComponent<TextComponent>().color = std::make_unique<Color>(color);
    } else
        ComponentStore::GetInstance().tryGetComponent<TextComponent>(entityID).color = std::make_unique<Color>(color);
}

void Button::SetFontPath(const std::string& path) {
    if (entityID == 0) {
        TryGetComponent<TextComponent>().fontPath = path;
    } else
        ComponentStore::GetInstance().tryGetComponent<TextComponent>(entityID).fontPath = path;
}

void Button::SetFontSize(int fontSize) {
    if (entityID == 0) {
        TryGetComponent<TextComponent>().fontSize = fontSize;
    } else
        ComponentStore::GetInstance().tryGetComponent<TextComponent>(entityID).fontSize = fontSize;
}

void Button::SetText(const std::string& string) {
    if (entityID == 0) {
        TryGetComponent<TextComponent>().text = string;
    } else
        ComponentStore::GetInstance().tryGetComponent<TextComponent>(entityID).text = string;
}

void Button::SetFill(const Color& color) {
    if (entityID == 0) {
        TryGetComponent<RectangleComponent>().fill = std::make_unique<Color>(color);
    } else
        ComponentStore::GetInstance().tryGetComponent<RectangleComponent>(entityID).fill = std::make_unique<Color>(color);
}

void Button::SetClickEvent(std::function<void()> func) {
    TryGetComponent<ClickableComponent>().OnClick = std::move(func);
}

void Button::SetBorderWidth(int borderWidth) {
    if (entityID == 0) {
        TryGetComponent<RectangleComponent>().borderWidth = borderWidth;
    } else
        ComponentStore::GetInstance().tryGetComponent<RectangleComponent>(entityID).borderWidth = borderWidth;
}

void Button::SetBorderColor(const Color& color) {
    if (entityID == 0) {
        TryGetComponent<RectangleComponent>().borderColor = std::make_unique<Color>(color);
    } else
        ComponentStore::GetInstance().tryGetComponent<RectangleComponent>(entityID).borderColor = std::make_unique<Color>(color);
}

bool Button::IsDisabled() const {
    return TryGetComponent<ClickableComponent>().disabled;
}

void Button::SetDisabled(bool disabled) {
    if (entityID == 0) {
        TryGetComponent<ClickableComponent>().disabled = disabled;
    } else
        ComponentStore::GetInstance().tryGetComponent<ClickableComponent>(entityID).disabled = disabled;
}
