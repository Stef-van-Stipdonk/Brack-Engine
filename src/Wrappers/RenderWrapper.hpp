//
// Created by jesse on 30/10/2023.
//

#ifndef BRACK_ENGINE_RENDERWRAPPER_HPP
#define BRACK_ENGINE_RENDERWRAPPER_HPP

#include <iostream>
#include "SDL.h"
#include <SDL_ttf.h>
#include "Components/CameraComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TextComponent.hpp"
#include <map>
#include <memory>
#include <Components/BoxCollisionComponent.hpp>
#include <Components/CircleCollisionComponent.hpp>
#include <Components/RectangleComponent.hpp>
#include <Components/CircleComponent.hpp>


struct SDLWindowDeleter {
    void operator()(SDL_Window* window) const {
        SDL_DestroyWindow(window);
    }
};

class RenderWrapper {
public:
    RenderWrapper();

    ~RenderWrapper();

    void RenderCamera(CameraComponent* camera);
    void RenderSprite(SpriteComponent &sprite);
    void RenderText(TextComponent* textComponent, TransformComponent* transformComponent);
    void RenderRectangle(RectangleComponent* rectangleComponent, TransformComponent* transformComponent);
    void RenderCircle(CircleComponent* circleComponent, TransformComponent* transformComponent);
    void RenderBoxCollisionComponents(BoxCollisionComponent* boxCollisionComponent, TransformComponent* transformComponent);
    void RenderCircleCollisionComponents(CircleCollisionComponent* circleCollisionComponent, TransformComponent* transformComponent);

    void RenderFrame();
    static void Cleanup();

private:
    bool Initialize();
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> getTexture(std::string filePath);
    std::unordered_map<std::string, std::map<int, TTF_Font*>> fontCache;
    std::map<std::string, std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> textures;
    std::unique_ptr<SDL_Window, SDLWindowDeleter> window;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> renderer;
};


#endif //BRACK_ENGINE_RENDERWRAPPER_HPP
