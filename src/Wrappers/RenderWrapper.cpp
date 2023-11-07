//
// Created by jesse on 30/10/2023.
//

#include "RenderWrapper.hpp"
#include "../includes/SystemManager.hpp"
#include "../ConfigSingleton.hpp"
#include "../Logger.hpp"

RenderWrapper::RenderWrapper() : renderer(nullptr, nullptr) {
    Initialize();
}

RenderWrapper::~RenderWrapper() {
    Cleanup();
}


bool RenderWrapper::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL2 initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create a window.
    // You can customize the window size, title, and other settings as needed.
    // For simplicity, this example creates a 800x600 window.
    SDL_Window *window = SDL_CreateWindow("Brack Engine Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,
                                          600, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        Cleanup();
        return false;
    }

    // Perform additional initialization as needed (e.g., renderer setup, resource loading).
    renderer = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>(
            SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED),
            [](SDL_Renderer *r) { SDL_DestroyRenderer(r); }
    );

    if (renderer == nullptr) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        Logger::GetInstance().Shutdown();
        SDL_DestroyWindow(window);
        Cleanup();
        return false;
    }

    return true;
}

void RenderWrapper::Cleanup() {
    // Perform cleanup as necessary
    Logger::GetInstance().Shutdown();
    SDL_Quit();
}

void RenderWrapper::RenderCamera(CameraComponent* camera) {
    auto &backgroundColor = camera->backgroundColor;
    SDL_SetRenderDrawColor(renderer.get(), backgroundColor.r, backgroundColor.g, backgroundColor.b,
                           backgroundColor.a); // RGBA format

    // Clear the screen with the background color.
    SDL_RenderClear(renderer.get());

    // Present the renderer (update the window).
    SDL_RenderPresent(renderer.get());
}

void RenderWrapper::RenderSprite(SpriteComponent &sprite) {
    SDL_Surface* spritesheetSurface = SDL_LoadBMP(sprite.spritePath.c_str());
    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    const int frameRate = 10;

    if (!spritesheetSurface) {
        printf("SDL Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Texture* spritesheetTexture = SDL_CreateTextureFromSurface(renderer.get(), spritesheetSurface);

    auto spriteSheetHeight = sprite.imageSize->getY();
    auto spriteSheetWidth = sprite.imageSize->getX();
    auto spriteWidth = sprite.spriteSize->getX();
    auto spriteHeight = sprite.spriteSize->getY();
    int spriteSheetAmount = std::round(spriteSheetWidth/spriteWidth) * std::round(spriteSheetHeight/spriteHeight);

    SDL_Rect spriteRectangles[spriteSheetAmount];
    int spriteIndex = 0;
    for (int i = 0; i < spriteSheetHeight; ++i) {
        for (int j = 0; j < spriteSheetWidth; ++j) {
            spriteRectangles[spriteIndex] = {static_cast<int>(j * spriteWidth), static_cast<int>(i * spriteHeight), static_cast<int>(spriteWidth), static_cast<int>(spriteHeight)};
            spriteIndex++;
            if (spriteIndex >= spriteSheetAmount) {
                break;
            }
        }
    }

    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - lastFrameTime >= 1000 / frameRate) {
        currentFrame = (currentFrame + 1) % spriteSheetAmount;
        lastFrameTime = currentTime;
    }

    SDL_RenderClear(renderer.get());

    SDL_Rect srcRect = spriteRectangles[currentFrame];
    SDL_Rect destRect = {static_cast<int>(sprite.position->getX()), static_cast<int>(sprite.position->getY()), srcRect.w, srcRect.h};
    SDL_RenderCopy(renderer.get(), spritesheetTexture, &srcRect, &destRect);
}

void RenderWrapper::RenderText(TextComponent &text) {

}

void RenderWrapper::RenderButton(TextComponent &button) {

}

void RenderWrapper::Run() {
        // Process events.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Close the window if the user presses the "X" button.
            if (event.type == SDL_QUIT) {
                ConfigSingleton::GetInstance().ToggleIsRunning();
            }
    }
}


void RenderWrapper::RenderFrame() {
    //Render dubble buffered frame
}