//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TEXTCOMPONENT_HPP
#define BRACK_ENGINE_TEXTCOMPONENT_HPP

#include <string>
#include <memory>
#include "IComponent.hpp"
#include "Helpers/Color.hpp"

struct TextComponent : public IComponent {
    std::string text, fontPath;
    int fontSize;
    std::unique_ptr<Color> color;
};

#endif //BRACK_ENGINE_TEXTCOMPONENT_HPP
