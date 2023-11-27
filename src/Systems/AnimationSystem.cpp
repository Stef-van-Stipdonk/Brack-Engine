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
    timePassed += deltaTime;
    Logger::GetInstance().Info(std::to_string(deltaTime));
    auto animationComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<AnimationComponent>();
    int newX = 0;
    int newY = 0;

    for (auto entityId: animationComponentIds) {

        auto &spriteComponent = ComponentStore::GetInstance().tryGetComponent<SpriteComponent>(entityId);

        auto &animationComponent = ComponentStore::GetInstance().tryGetComponent<AnimationComponent>(entityId);
        animationComponent.animateTime += deltaTime;
        if (animationComponent.animateTime >= animationComponent.animationDuration / animationComponent.frameCount) {
            animationComponent.animateTime -= animationComponent.animationDuration / animationComponent.frameCount;
            animationComponent.currentFrame++;
            if (animationComponent.currentFrame >= animationComponent.frameCount) {
                animationComponent.currentFrame = 0;
            }
        }
        Logger::GetInstance().Debug(std::to_string(animationComponent.currentFrame));
        int spriteWidth = round(spriteComponent.imageSize->getX() / spriteComponent.spriteSize->getX());

        newX = animationComponent.currentFrame % spriteWidth;
        newY = animationComponent.currentFrame / spriteWidth;
        Logger::GetInstance().Debug(std::to_string(animationComponent.currentFrame));
        Logger::GetInstance().Debug(std::to_string(newX) + ", " + std::to_string(newY));

        spriteComponent.tileOffset->setX(newX);
        spriteComponent.tileOffset->setY(newY);


    }


}

const std::string AnimationSystem::getName() const {
    return "AnimationSystem";
}

void AnimationSystem::cleanUp() {
}
