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
#include <Components/Archetypes/RenderArchetype.hpp>

struct SpriteComponent : public RenderArchetype {
    explicit SpriteComponent() : RenderArchetype() {}

    ~SpriteComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<SpriteComponent>(this);
    }

    std::string spritePath;
    std::unique_ptr<Vector2> imageSize, spriteSize, tileOffset;
    std::unique_ptr<Color> color;
    bool flipX, flipY;
    int margin;
};

#endif //BRACK_ENGINE_SPRITECOMPONENT_HPP
