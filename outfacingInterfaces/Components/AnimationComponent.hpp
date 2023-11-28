//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_ANIMATIONCOMPONENT_HPP
#define BRACK_ENGINE_ANIMATIONCOMPONENT_HPP

#include <memory>
#include "SpriteComponent.hpp"

struct AnimationComponent : public IComponent {

    explicit AnimationComponent() : IComponent() {
    }

    ~AnimationComponent() override {
        if (startPosition != nullptr)
            startPosition = nullptr;
    };

    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<AnimationComponent>(*this);
    }

    AnimationComponent(const AnimationComponent &other) : IComponent(other) {
        isLooping = other.isLooping;
        animationDuration = other.animationDuration;
        endFrame = other.endFrame;
        currentFrame = other.currentFrame;
        elapsedTime = other.elapsedTime;
        if (other.startPosition != nullptr)
            startPosition = std::make_unique<Vector2>(*other.startPosition);
    }

    bool isLooping = true;
    float animationDuration = 0.0f;
    float elapsedTime = 0.0f;
    int endFrame, currentFrame = 0;
    std::unique_ptr<Vector2> startPosition = std::make_unique<Vector2>(0, 0);
};

#endif //BRACK_ENGINE_ANIMATIONCOMPONENT_HPP
