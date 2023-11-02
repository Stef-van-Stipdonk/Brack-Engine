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
    BrackEngine();

    ~BrackEngine() = default;

    void Initialize();

    void Update();

    EntityManager &GetEntityManager() const;

    SystemManager &GetSystemManager() const;

    SceneManager &GetSceneManager() const;

    ReplayManager &GetReplayManager() const;

    InputManager &GetInputManager() const;

private:
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<SystemManager> systemManager;
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<ReplayManager> replayManager;
    std::shared_ptr<InputManager> inputManager;
};


#endif //BRACK_ENGINE_BRACKENGINE_HPP
