//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_BRACKENGINE_HPP
#define BRACK_ENGINE_BRACKENGINE_HPP


#include <chrono>
#include "EngineManagers/SceneManager.hpp"
#include "Config.hpp"

class BrackEngine {
public:
    BrackEngine(Config &&config);

    ~BrackEngine() = default;

    void Run();
private:
    milliseconds GetDeltaTime();

    void CreateFPS();

    void UpdateFPS(float deltaTime);

    std::shared_ptr<std::chrono::time_point<std::chrono::high_resolution_clock> > lastTime = std::make_shared<
        std::chrono::time_point<std::chrono::high_resolution_clock> >();

    bool shouldResetLastTime = false;

    float totalTime = 0;
    float &deltaTimeMultiplier;
};


#endif //BRACK_ENGINE_BRACKENGINE_HPP
