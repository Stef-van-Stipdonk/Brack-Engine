//
// Created by jesse on 07/11/2023.
//

#include "FPSWrapper.hpp"
#include "ConfigSingleton.hpp"

void FPSWrapper::Start() {
    start = SDL_GetPerformanceCounter();
}

void FPSWrapper::End() {
    auto fpsLimit = ConfigSingleton::getInstance().getFPSLimit();
    auto frameDelay = 1000.0f / fpsLimit;
    end = SDL_GetPerformanceCounter();
    float elapsed = (end - start) / (float) SDL_GetPerformanceFrequency();

    if (fpsLimit > 0) {
        float delayTime = floor(frameDelay - elapsed);

        // Ensure a positive delay time to avoid negative delays
        if (delayTime > 0.0f) {
            Uint32 delayMilliseconds = static_cast<Uint32>(delayTime);
            SDL_Delay(delayMilliseconds);
            end = SDL_GetPerformanceCounter();
            elapsed = (end - start) / (float) SDL_GetPerformanceFrequency();
        }
    }

    fps = (int) (1.0f / elapsed);
}

int FPSWrapper::GetFPS() const {
    return fps;
}
