//
// Created by jesse on 31/10/2023.
//

#include <Components/AnimationComponent.hpp>
#include "AnimationSystem.hpp"
#include "../includes/ComponentStore.hpp"

AnimationSystem::AnimationSystem() {

}

AnimationSystem::~AnimationSystem() {

}

void AnimationSystem::update(float deltaTime) {
    auto animationComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<AnimationComponent>();
    int newX = 0;
    int newY = 0;

    for (auto entityId: animationComponentIds) {

        auto &spriteComponent = ComponentStore::GetInstance().tryGetComponent<SpriteComponent>(entityId);
        auto &animationComponent = ComponentStore::GetInstance().tryGetComponent<AnimationComponent>(entityId);
        if (animationComponent.isLooping) {
            animationComponent.elapsedTime += deltaTime;
            if (animationComponent.elapsedTime >= animationComponent.animationDuration / animationComponent.endFrame) {
                animationComponent.elapsedTime -= animationComponent.animationDuration / animationComponent.endFrame;
                animationComponent.currentFrame++;

                if (animationComponent.currentFrame > animationComponent.endFrame) {
                    spriteComponent.tileOffset = std::make_unique<Vector2>(*animationComponent.startPosition);
                    animationComponent.currentFrame =
                            spriteComponent.tileOffset->getX() +
                            spriteComponent.tileOffset->getY() *
                            round(spriteComponent.imageSize->getX() / spriteComponent.spriteSize->getX());

                    continue;

                }
                int spriteAmountX = round(spriteComponent.imageSize->getX() / spriteComponent.spriteSize->getX());

                int spriteIndex = animationComponent.currentFrame;
                newX = spriteIndex % spriteAmountX;
                newY = spriteIndex / spriteAmountX;
                spriteComponent.tileOffset = std::make_unique<Vector2>(newX, newY);

            }
        }


    }


}

const std::string AnimationSystem::getName() const {
    return "AnimationSystem";
}

void AnimationSystem::cleanUp() {
}
