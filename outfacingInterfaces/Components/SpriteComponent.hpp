//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_SPRITECOMPONENT_HPP
#define BRACK_ENGINE_SPRITECOMPONENT_HPP

#include "TransformComponent.hpp"
#include "Helpers/Color.hpp"
#include <string>
#include <memory>

struct SpriteComponent : public TransformComponent {
    explicit SpriteComponent(uint32_t entityId) : TransformComponent(entityId) {}

    ~SpriteComponent() override = default;

    std::string spritePath;
    std::unique_ptr<Vector2> imageSize, spriteSize, tileOffset;
    std::unique_ptr<Color> color;
    bool flipX, flipY;
    int sortingLayer, orderInLayer;
};

#endif //BRACK_ENGINE_SPRITECOMPONENT_HPP
