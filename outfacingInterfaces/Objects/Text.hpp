//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TEXT_HPP
#define BRACK_ENGINE_TEXT_HPP

#include <memory>
#include "UIObject.hpp"
#include "Helpers/Color.hpp"

class Text : public UIObject {
public:
    Text(std::string text, int fontSize, std::unique_ptr<Color> color, std::string fontPath);
    Text(std::string text, int fontSize, std::unique_ptr<Color> color);
    Text(std::string text, int fontSize);
    Text(std::string text);

    ~Text() override = default;

    void SetText(const std::string text);

    std::string GetText() const;

    void SetFontPath(const std::string font);

    std::string GetFont() const;

    void SetFontSize(const int fontSize);

    int GetFontSize() const;

    void SetColor(const Color &color);

    Color &GetColor() const;
};


#endif //BRACK_ENGINE_TEXT_HPP
