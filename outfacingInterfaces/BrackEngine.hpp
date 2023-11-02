//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_BRACKENGINE_HPP
#define BRACK_ENGINE_BRACKENGINE_HPP


#include <memory>
#include "../src/includes/EntityManager.hpp"
#include "../src/includes/SystemManager.hpp"
#include "Engine Managers/SceneManager.hpp"
#include "Engine Managers/ReplayManager.hpp"
#include "Engine Managers/InputManager.hpp"

class BrackEngine {
public:
    BrackEngine() = default;

    ~BrackEngine() = default;

    void Update();
};


#endif //BRACK_ENGINE_BRACKENGINE_HPP
