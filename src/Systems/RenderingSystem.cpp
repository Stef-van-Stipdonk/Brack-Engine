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
    auto cameras = ComponentStore::GetInstance().getEntitiesWithComponent<CameraComponent>();
    for (auto cameraId: cameras) {
        auto cameraComponent = ComponentStore::GetInstance().tryGetComponent<CameraComponent>(cameraId);
        auto cameraTransformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(cameraId);
        sdl2Wrapper->RenderCamera(cameraComponent, cameraTransformComponent);
        for (auto& component: components) {
            auto transformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(
                    component.entityID);
            if (auto *spriteComponent = dynamic_cast<const SpriteComponent*>(&component))
                sdl2Wrapper->RenderComponent(cameraComponent, *spriteComponent, cameraTransformComponent);
            else if (auto* textComponent = dynamic_cast<const TextComponent*>(&component))
                sdl2Wrapper->RenderComponent(cameraComponent, *textComponent, transformComponent);
        }
    }

#if CURRENT_LOG_LEVEL >= LOG_LEVEL_DEBUG
    auto boxCollisionComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<BoxCollisionComponent>();
    for (int entityId: boxCollisionComponentIds) {
        auto boxCollisionComponent = ComponentStore::GetInstance().tryGetComponent<BoxCollisionComponent>(entityId);
        auto transformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(entityId);
        sdl2Wrapper->RenderBoxCollisionComponents(boxCollisionComponent, transformComponent);
    }

    auto circleCollisionComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<CircleCollisionComponent>();
    for (int entityId: circleCollisionComponentIds) {
        auto circleCollisionComponent = ComponentStore::GetInstance().tryGetComponent<CircleCollisionComponent>(entityId);
        auto transformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(entityId);
        sdl2Wrapper->RenderCircleCollisionComponents(circleCollisionComponent, transformComponent);
    }
#endif
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
    auto spriteComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<SpriteComponent>();
    for (uint32_t entityId: spriteComponentIds) {
        components.insert(ComponentStore::GetInstance().tryGetComponent<SpriteComponent>(entityId));
    }
    auto textComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<TextComponent>();
    for (uint32_t entityId: textComponentIds) {
        auto textComponent = ComponentStore::GetInstance().tryGetComponent<TextComponent>(entityId);
        components.insert(textComponent);
    }
}
