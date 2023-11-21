//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BUTTON_HPP
#define BRACK_ENGINE_BUTTON_HPP


#include <Helpers/Color.hpp>
#include <functional>
#include "UIObject.hpp"

class Button : public UIObject {
public:
    Button(const Vector2& size, const std::string& text);

    ~Button() = default;

    void SetText(const std::string& string);
    void SetTextColor(const Color& color);
    void SetBorderWidth(int borderWidth);
    void SetBorderColor(const Color& color);
    void SetFill(const Color& color);
    void SetFontPath(const std::string& path);
    void SetFontSize(int fontSize);
    void SetClickEvent(std::function<void()> func);
    bool IsDisabled() const;
    void SetDisabled(bool disabled);
};

#endif //BRACK_ENGINE_BUTTON_HPP