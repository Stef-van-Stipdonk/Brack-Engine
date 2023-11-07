//
// Created by jesse on 31/10/2023.
//

#include <SDL.h>
#include "../EngineManagers/InputManager.hpp"
#include "InputWrapper.hpp"
#include "../Logger.hpp"
#include "../ConfigSingleton.hpp"

InputWrapper::InputWrapper() {

}

InputWrapper::~InputWrapper() {

}

void InputWrapper::HandleEvents() {
    // Process events.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Close the window if the user presses the "X" button.
        if (event.type == SDL_QUIT) {
            ConfigSingleton::GetInstance().ToggleIsRunning();
        }

        if (event.type == SDL_KEYDOWN){
            Logger::Debug("key down");
        }

        if (event.type == SDL_MOUSEMOTION){
            InputManager::GetInstance().SetMousePosition(
        Vector2(
                static_cast<float>(event.motion.x),
                static_cast<float>(event.motion.y)
                )
            );
        }

        if (event.type == SDL_MOUSEBUTTONDOWN){
            Logger::Debug("mouse down");
        }
    }
}
