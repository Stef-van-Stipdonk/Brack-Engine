//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_BRACKENGINE_HPP
#define BRACK_ENGINE_BRACKENGINE_HPP


#include <memory>
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

    void Update();
    bool isRunning = true;
private:
};


#endif //BRACK_ENGINE_BRACKENGINE_HPP
