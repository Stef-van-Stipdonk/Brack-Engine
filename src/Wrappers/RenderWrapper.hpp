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

    void RenderSprite(SpriteComponent &sprite);

    void RenderText(TextComponent &text);

    void RenderButton(TextComponent &button);

private:

    bool Initialize();

    void Cleanup();

    std::map<std::string, SDL_Texture *> textures;
};


#endif //BRACK_ENGINE_RENDERWRAPPER_HPP
