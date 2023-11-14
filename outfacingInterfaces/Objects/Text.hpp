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
    explicit Text(const std::string& text);

    ~Text()  = default;

    void SetText(const std::string& text);

    void SetFontPath(const std::string& font);

    void SetFontSize(int fontSize);

    void SetColor(const Color& color);

};


#endif //BRACK_ENGINE_TEXT_HPP
