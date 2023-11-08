//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_ANIMATIONCOMPONENT_HPP
#define BRACK_ENGINE_ANIMATIONCOMPONENT_HPP

#include <memory>
#include "SpriteComponent.hpp"

struct AnimationComponent : public SpriteComponent {

    explicit AnimationComponent() : SpriteComponent() {}

    ~AnimationComponent() override = default;

    void Accept(IComponentVisitor &visitor) override {
        visitor.visit(this);
    }

    bool isLooping;
    float animationSpeed;
    int frameCount, currentFrame;
    std::unique_ptr<Vector2> startPosition;
};

#endif //BRACK_ENGINE_ANIMATIONCOMPONENT_HPP
