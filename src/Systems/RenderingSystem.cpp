//
// Created by jesse on 31/10/2023.
//

#include "RenderingSystem.hpp"
#include "../includes/ComponentStore.hpp"

RenderingSystem::RenderingSystem() : sdl2Wrapper(new RenderWrapper()) {
}

RenderingSystem::~RenderingSystem() {

}

void RenderingSystem::Update(float deltaTime) {
    //Render camera
    try {
        auto &component = ComponentStore::GetInstance().GetComponent<CameraComponent>(1);
        sdl2Wrapper->RenderCamera(component);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
