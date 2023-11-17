#include <Components/TextComponent.hpp>
#include "TextComponentLoad.h"

std::unique_ptr<IComponent> TextComponentLoad::Load() const {
    return std::make_unique<TextComponent>();
}
