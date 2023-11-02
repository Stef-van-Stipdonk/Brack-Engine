//
// Created by jesse on 02/11/2023.
//

#ifndef BRACK_ENGINE_REPLAYMANAGER_HPP
#define BRACK_ENGINE_REPLAYMANAGER_HPP

#include <string>

class ReplayManager {
public:
    ReplayManager() = default;

    ~ReplayManager() = default;

    void StartReplay(std::string filePath);

    void PauseReplay();

    void StopReplayCapture();

    void StartReplayPlayback(std::string filePath);

    void PauseReplayPlayback();

    void StopReplayPlayback();

};


#endif //BRACK_ENGINE_REPLAYMANAGER_HPP
