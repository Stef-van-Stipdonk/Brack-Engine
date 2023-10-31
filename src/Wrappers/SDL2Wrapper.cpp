//
// Created by jesse on 30/10/2023.
//

#include "SDL2Wrapper.hpp"

SDL2Wrapper::SDL2Wrapper() {

}

SDL2Wrapper::~SDL2Wrapper() {
    Cleanup();
}


bool SDL2Wrapper::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL2 initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create a window.
    // You can customize the window size, title, and other settings as needed.
    // For simplicity, this example creates a 800x600 window.
    SDL_Window* window = SDL_CreateWindow("Brack Engine Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Perform additional initialization as needed (e.g., renderer setup, resource loading).

    return true;
}

void SDL2Wrapper::Run() {
    // Run the event loop
    bool isRunning = true;
    SDL_Event event;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Render your content here

        // You can add rendering code here.

        // Delay to control frame rate (optional)
        SDL_Delay(16);
    }
}

void SDL2Wrapper::Cleanup() {
    // Perform cleanup as necessary
    SDL_Quit();
}



