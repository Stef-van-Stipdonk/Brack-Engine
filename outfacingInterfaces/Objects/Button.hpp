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
    Button(Vector2 size, std::string text);

    ~Button() = default;

    void SetText(std::string string);
    void SetTextColor(Color color);
    void SetBorderWidth(int borderWidth);
    void SetBorderColor(Color color);
    void SetFill(Color color);
    void SetFontPath(std::string path);
    void SetFontSize(int fontSize);
    void SetClickEvent(std::function<void()> func);
    bool IsDisabled() const;
    void SetDisabled(const bool disabled);
};


#endif //BRACK_ENGINE_BUTTON_HPP
