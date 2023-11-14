//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_SPRITECOMPONENT_HPP
#define BRACK_ENGINE_SPRITECOMPONENT_HPP

#include "TransformComponent.hpp"
#include "Helpers/Color.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include <string>
#include <memory>

struct SpriteComponent : public TransformComponent {
    explicit SpriteComponent() : TransformComponent() {}

    ~SpriteComponent() override {
        if(imageSize != nullptr)
            imageSize = nullptr;

        if(spriteSize != nullptr)
            spriteSize = nullptr;

        if(tileOffset != nullptr)
            tileOffset = nullptr;

        if(color != nullptr)
            color = nullptr;
    };

    std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<SpriteComponent>(*this);
    }

    SpriteComponent(const SpriteComponent &other) : TransformComponent(other) {
        spritePath = other.spritePath;
        if(other.imageSize != nullptr)
            imageSize = std::make_unique<Vector2>(*other.imageSize);

        if(other.spriteSize != nullptr)
            spriteSize = std::make_unique<Vector2>(*other.spriteSize);

        if(other.tileOffset != nullptr)
            tileOffset = std::make_unique<Vector2>(*other.tileOffset);

        if(other.color != nullptr)
            color = std::make_unique<Color>(*other.color);

        flipX = other.flipX;
        flipY = other.flipY;
        sortingLayer = other.sortingLayer;
        orderInLayer = other.orderInLayer;
        margin = other.margin;
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::string spritePath;
    std::unique_ptr<Vector2> imageSize, spriteSize, tileOffset;
    std::unique_ptr<Color> color;
    bool flipX, flipY;
    int sortingLayer, orderInLayer;
    int margin;
};

#endif //BRACK_ENGINE_SPRITECOMPONENT_HPP
