//
// Created by Stijn Laptop on 16-11-2023.
//

#include <Components/SpriteComponent.hpp>
#include "SpriteComponentLoad.h"

std::unique_ptr<IComponent> SpriteComponentLoad::Load() const {
    return std::make_unique<SpriteComponent>();
}
