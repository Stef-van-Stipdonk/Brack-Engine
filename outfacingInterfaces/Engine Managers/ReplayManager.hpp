//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_REPLAYMANAGER_HPP
#define BRACK_ENGINE_REPLAYMANAGER_HPP

#include <string>
#include <memory>
#include "../../src/includes/EntityManager.hpp"

class ReplayManager {
public:
    ReplayManager() = default;

    ~ReplayManager() = default;

    void Initialize(std::shared_ptr<EntityManager> newEntityManager);

    void StartReplay(std::string filePath);

    void PauseReplay();

    void StopReplayCapture();

    void StartReplayPlayback(std::string filePath);

    void PauseReplayPlayback();

    void StopReplayPlayback();

private:
    std::shared_ptr<EntityManager> entityManager;
};


#endif //BRACK_ENGINE_REPLAYMANAGER_HPP
