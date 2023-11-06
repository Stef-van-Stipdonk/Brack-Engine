//
// Created by jesse on 30/10/2023.
//

#ifndef BRACK_ENGINE_RENDERWRAPPER_HPP
#define BRACK_ENGINE_RENDERWRAPPER_HPP

#include <iostream>
#include "SDL.h"
#include "Components/CameraComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TextComponent.hpp"
#include <map>
#include <memory>


class RenderWrapper {
public:
    RenderWrapper();

    ~RenderWrapper();

    void Run(); //Alleen om te testen

    void RenderCamera(CameraComponent* camera);

    void RenderSprite(SpriteComponent &sprite);

    void RenderText(TextComponent &text);

    void RenderButton(TextComponent &button);

    void RenderFrame();

    static void Cleanup();

private:

    bool Initialize();

    std::map<std::string, SDL_Texture *> textures;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> renderer;
};


#endif //BRACK_ENGINE_RENDERWRAPPER_HPP
