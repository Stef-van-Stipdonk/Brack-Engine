//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_SPRITECOMPONENT_HPP
#define BRACK_ENGINE_SPRITECOMPONENT_HPP

#include "TransformComponent.hpp"
#include "Helpers/Color.hpp"
#include <string>

struct SpriteComponent : public TransformComponent {
    SpriteComponent() = default;

    ~SpriteComponent() override = default;

    std::string spritePath;
    Vector2 imageSize, spriteSize, tileOffset;
    Color color;
    bool flipX, flipY;
    int sortingLayer, orderInLayer;
};

#endif //BRACK_ENGINE_SPRITECOMPONENT_HPP
