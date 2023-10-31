//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TEXT_HPP
#define BRACK_ENGINE_TEXT_HPP


#include "UIObject.hpp"
#include "Helpers/Color.hpp"

class Text : public UIObject {
public:
    Text() = default;

    ~Text() override = default;

    void SetText(const char *text);

    std::string GetText() const;

    void SetFont(const char *font);

    std::string GetFont() const;

    void SetFontSize(const int fontSize);

    int GetFontSize() const;

    void SetColor(const Color color);

    Color GetColor() const;
};


#endif //BRACK_ENGINE_TEXT_HPP
