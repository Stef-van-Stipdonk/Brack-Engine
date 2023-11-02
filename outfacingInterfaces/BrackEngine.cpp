//
// Created by jesse on 02/11/2023.
//

#include "BrackEngine.hpp"

BrackEngine::BrackEngine() : entityManager(new EntityManager()), systemManager(new SystemManager()),
                             sceneManager(new SceneManager()),
                             replayManager(new ReplayManager()), inputManager(new InputManager()) {


}

EntityManager &BrackEngine::GetEntityManager() const {
    return *entityManager;
}

SystemManager &BrackEngine::GetSystemManager() const {
    return *systemManager;
}

SceneManager &BrackEngine::GetSceneManager() const {
    return *sceneManager;
}

ReplayManager &BrackEngine::GetReplayManager() const {
    return *replayManager;
}

InputManager &BrackEngine::GetInputManager() const {
    return *inputManager;
}

void BrackEngine::Initialize() {
    entityManager->Initialize();
    sceneManager->Initialize(entityManager);
    replayManager->Initialize(entityManager);
    inputManager->Initialize(entityManager);
}

void BrackEngine::Update() {
    
}
