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
    Text(std::string text, int fontSize, Color color, std::string fontPath);
    Text(std::string text, int fontSize, Color color);
    Text(std::string text, int fontSize);
    Text(std::string text);
};


#endif //BRACK_ENGINE_TEXT_HPP
