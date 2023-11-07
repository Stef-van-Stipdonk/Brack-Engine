//
// Created by jesse on 31/10/2023.
//

#include "RenderingSystem.hpp"
#include "../includes/ComponentStore.hpp"
#include "../Logger.hpp"
#include "../includes/EntityManager.hpp"

RenderingSystem::RenderingSystem() : sdl2Wrapper(new RenderWrapper()) {
}

RenderingSystem::~RenderingSystem() {

}

void RenderingSystem::Update(float deltaTime) {
    //Render camera
    try {
        auto& instance = ComponentStore::GetInstance();
        auto component = instance.getComponent<CameraComponent>(1);
//        Logger::Debug(std::string(reinterpret_cast<const char *>(component->entityID)));
        sdl2Wrapper->RenderCamera(component);

        auto entities = instance.getEntitiesWithComponent<SpriteComponent>();
        for(auto& entity : entities) {
            auto sprite = instance.getComponent<SpriteComponent>(entity);
            if(sprite == nullptr)
                continue;

            sdl2Wrapper->RenderSprite(*sprite);
        }

        sdl2Wrapper->Run();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void RenderingSystem::CleanUp() {
    sdl2Wrapper->Cleanup();
}

const std::string RenderingSystem::GetName() const {
    return "RenderingSystem";
}
