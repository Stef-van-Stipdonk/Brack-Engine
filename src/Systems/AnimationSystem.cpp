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
    for (auto entityId: animationComponentIds) {
        auto &spriteComponent = ComponentStore::GetInstance().tryGetComponent<SpriteComponent>(entityId);

/*        auto &animationComponent = ComponentStore::GetInstance().tryGetComponent<AnimationComponent>(entityId);
            int totalFrames = animationComponent.frameCount;
            float frameDuration = animationComponent.animationDuration / totalFrames;

            animationComponent.currentFrame += static_cast<int>(deltaTime / frameDuration);

            // Reset to the first frame if looping
            if (animationComponent.isLooping) {
                animationComponent.currentFrame %= totalFrames;
            } else {
                // Clamp to the last frame if not looping
                animationComponent.currentFrame = std::min(animationComponent.currentFrame, totalFrames - 1);


        }*/

        if (spriteComponent.spriteSize->getX() * (spriteComponent.tileOffset->getX() + 1) >
            spriteComponent.imageSize->getX()) {
            spriteComponent.tileOffset->setX(0);
        } else {
            spriteComponent.tileOffset->setX(spriteComponent.tileOffset->getX() + 1);
        }


    }


}

const std::string AnimationSystem::getName() const {
    return "AnimationSystem";
}

void AnimationSystem::cleanUp() {
}
