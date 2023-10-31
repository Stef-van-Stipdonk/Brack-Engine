//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_ANIMATIONCOMPONENT_HPP
#define BRACK_ENGINE_ANIMATIONCOMPONENT_HPP

#include "SpriteComponent.hpp"

class AnimationComponent : public SpriteComponent {
public:
    AnimationComponent() = default;

    ~AnimationComponent() override = default;

    bool isLooping;
    float animationSpeed;
    int frameCount, currentFrame;
    Vector2 startPosition;
};

#endif //BRACK_ENGINE_ANIMATIONCOMPONENT_HPP
