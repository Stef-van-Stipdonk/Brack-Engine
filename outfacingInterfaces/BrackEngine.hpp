//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_BRACKENGINE_HPP
#define BRACK_ENGINE_BRACKENGINE_HPP


#include <memory>
#include <chrono>
#include "../src/includes/EntityManager.hpp"
#include "../src/includes/SystemManager.hpp"
#include "EngineManagers/SceneManager.hpp"
#include "EngineManagers/ReplayManager.hpp"
#include "EngineManagers/InputManager.hpp"
#include "Config.hpp"

class BrackEngine {
public:
    BrackEngine(Config &&config);

    ~BrackEngine() = default;

    void Run();
private:
    float GetDeltaTime();
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
};


#endif //BRACK_ENGINE_BRACKENGINE_HPP
