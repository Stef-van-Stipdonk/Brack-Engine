//
// Created by Stef van Stipdonk on 30/11/2023.
//

#include "EngineManagers/ReplayManager.hpp"
#include "../Systems/ReplaySystem.hpp"
#include "../includes/SystemManager.hpp"

ReplayManager &ReplayManager::getInstance() {
    static ReplayManager instance;
    return instance;
}

void ReplayManager::startRecording(milliseconds replayStorageDuration, milliseconds snapshotIntervalDuration) {
    SystemManager::getInstance().GetSystem<ReplaySystem>().lock()->startRecording(replayStorageDuration,
                                                                                  snapshotIntervalDuration);
}

void ReplayManager::stopRecording() {
    SystemManager::getInstance().GetSystem<ReplaySystem>().lock()->stopRecording();
}

void ReplayManager::clear() {
    SystemManager::getInstance().GetSystem<ReplaySystem>().lock()->cleanUp();
    SystemManager::getInstance().GetSystem<ReplaySystem>().lock()->clearCache();

}

void ReplayManager::toggleReplay() {
    SystemManager::getInstance().GetSystem<ReplaySystem>().lock()->toggleReplay();
}