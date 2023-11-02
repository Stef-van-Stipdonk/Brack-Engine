//
// Created by jesse on 30/10/2023.
//

#include "RenderWrapper.hpp"

RenderWrapper::RenderWrapper() {
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
        SDL_Quit();
        return false;
    }

    // Perform additional initialization as needed (e.g., renderer setup, resource loading).
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    // Set the background color (e.g., red in this case).
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // RGBA format

    // Clear the screen with the background color.
    SDL_RenderClear(renderer);

    // Present the renderer (update the window).
    SDL_RenderPresent(renderer);


    return true;
}

void RenderWrapper::Cleanup() {
    // Perform cleanup as necessary
    SDL_Quit();
}

void RenderWrapper::RenderSprite(SpriteComponent &sprite) {

}

void RenderWrapper::RenderText(TextComponent &text) {

}

void RenderWrapper::RenderButton(TextComponent &button) {

}

void RenderWrapper::Run() {
    // Run the game loop.
    bool gameLoopActive = true;
    while (gameLoopActive) {
        // Process events.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Close the window if the user presses the "X" button.
            if (event.type == SDL_QUIT) {
                gameLoopActive = false;
            }
        }

        // Perform game logic here.

        // Render stuff.
    }
}



