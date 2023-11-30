//
// Created by Stef van Stipdonk on 30/11/2023.
//

#ifndef BRACKOCALYPSE_REPLAYMANAGER_HPP
#define BRACKOCALYPSE_REPLAYMANAGER_HPP

#include <Milliseconds.hpp>

class ReplayManager {
public:
    ReplayManager &getInstance();

    void startRecording(milliseconds replayStorageDuration, milliseconds snapshotIntervalDuration);

    void stopRecording();

    void toggleReplay();

private:
    ReplayManager() = default;

    ~ReplayManager() = default;

    ReplayManager(const ReplayManager &) = delete;

    ReplayManager &operator=(const ReplayManager &) = delete;

    ReplayManager(ReplayManager &&) = delete;

    ReplayManager &operator=(ReplayManager &&) = delete;
};


#endif //BRACKOCALYPSE_REPLAYMANAGER_HPP
