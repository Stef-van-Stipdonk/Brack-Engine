//
// Created by jesse on 31/10/2023.
//

#include <Components/Archetypes/RenderArchetype.hpp>
#include "RenderingSystem.hpp"
#include "../includes/ComponentStore.hpp"
#include "../Logger.hpp"
#include "../includes/EntityManager.hpp"

RenderingSystem::RenderingSystem() : sdl2Wrapper(new RenderWrapper()) {
}

RenderingSystem::~RenderingSystem() {

}

void RenderingSystem::Update(float deltaTime) {
    SortRenderComponents();
#if CURRENT_LOG_LEVEL >= LOG_LEVEL_DEBUG
    auto boxCollisionComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<BoxCollisionComponent>();
    auto circleCollisionComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<CircleCollisionComponent>();
#endif
    auto cameras = ComponentStore::GetInstance().getEntitiesWithComponent<CameraComponent>();
    for (auto cameraId: cameras) {
        auto &cameraComponent = ComponentStore::GetInstance().tryGetComponent<CameraComponent>(cameraId);
        if (!cameraComponent.isActive)
            continue;
        auto &cameraTransformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(cameraId);
        sdl2Wrapper->RenderCamera(cameraComponent, cameraTransformComponent);
        for (auto component: components) {
            auto &transformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(
                    component->entityID);
            if (auto *spriteComponent = dynamic_cast<const SpriteComponent *>(component))
                sdl2Wrapper->RenderSprite(cameraComponent, cameraTransformComponent, *spriteComponent,
                                          transformComponent);
            else if (auto *textComponent = dynamic_cast<const TextComponent *>(component))
                sdl2Wrapper->RenderText(cameraComponent, cameraTransformComponent, *textComponent, transformComponent);
            else if (auto *rectangleComponent = dynamic_cast<const RectangleComponent *>(component))
                sdl2Wrapper->RenderRectangle(cameraComponent, cameraTransformComponent, *rectangleComponent,
                                             transformComponent);
        }
#if CURRENT_LOG_LEVEL >= LOG_LEVEL_DEBUG
        for (auto entityId: boxCollisionComponentIds) {
            auto &boxCollisionComponent = ComponentStore::GetInstance().tryGetComponent<BoxCollisionComponent>(
                    entityId);
            auto &transformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(entityId);
            sdl2Wrapper->RenderBoxCollision(cameraComponent, cameraTransformComponent, boxCollisionComponent,
                                            transformComponent);
        }

        for (auto entityId: circleCollisionComponentIds) {
            auto &circleCollisionComponent = ComponentStore::GetInstance().tryGetComponent<CircleCollisionComponent>(
                    entityId);
            auto &transformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(entityId);
            sdl2Wrapper->RenderCircleCollision(cameraComponent, cameraTransformComponent, circleCollisionComponent,
                                               transformComponent);
        }
#endif
    }

    sdl2Wrapper->RenderToMainTexture();

    for (auto component: uiComponents) {
        auto &transformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(
                component->entityID);
        if (auto *spriteComponent = dynamic_cast<const SpriteComponent *>(component))
            sdl2Wrapper->RenderUiSprite(*spriteComponent, transformComponent);
        else if (auto *textComponent = dynamic_cast<const TextComponent *>(component))
            sdl2Wrapper->RenderUiText(*textComponent, transformComponent);
        else if (auto *rectangleComponent = dynamic_cast<const RectangleComponent *>(component))
            sdl2Wrapper->RenderUiRectangle(*rectangleComponent, transformComponent);
    }
    sdl2Wrapper->RenderFrame();

}

void RenderingSystem::CleanUp() {
    sdl2Wrapper->Cleanup();
}

const std::string RenderingSystem::GetName() const {
    return "RenderingSystem";
}

void RenderingSystem::SortRenderComponents() {
    components.clear();
    uiComponents.clear();

    auto spriteComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<SpriteComponent>();
    for (uint32_t entityId: spriteComponentIds) {
        auto &spriteComponent = ComponentStore::GetInstance().tryGetComponent<SpriteComponent>(entityId);
        if (!spriteComponent.isActive)
            continue;
        if (spriteComponent.sortingLayer == 0) // UI layer
            uiComponents.insert(&spriteComponent);
        else
            components.insert(&spriteComponent);
    }
    auto textComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<TextComponent>();
    for (uint32_t entityId: textComponentIds) {
        auto &textComponent = ComponentStore::GetInstance().tryGetComponent<TextComponent>(entityId);
        if (!textComponent.isActive)
            continue;
        if (textComponent.sortingLayer == 0) // UI layer
            uiComponents.insert(&textComponent);
        else
            components.insert(&textComponent);
    }
    auto RectangleComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<RectangleComponent>();
    for (uint32_t entityId: RectangleComponentIds) {
        auto &rectangleComponent = ComponentStore::GetInstance().tryGetComponent<RectangleComponent>(entityId);
        if (!rectangleComponent.isActive)
            continue;
        if (rectangleComponent.sortingLayer == 0) // UI layer
            uiComponents.insert(&rectangleComponent);
        else
            components.insert(&rectangleComponent);
    }
}
