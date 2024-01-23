//
// Created by Stef van Stipdonk on 28/11/2023.
//

#include "ReplaySystem.hpp"

#include "AudioSystem.hpp"
#include "RenderingSystem.hpp"
#include "../includes/BehaviourScriptStore.hpp"

ReplaySystem::ReplaySystem(bool shouldResetLastTime) : shouldResetLastTime(shouldResetLastTime) {
}

ReplaySystem::~ReplaySystem() {
    cleanUp();
}

void ReplaySystem::toggleReplay() {
    replayStart = true;
}

void ReplaySystem::startRecording(milliseconds replayStorageDuration, milliseconds snapshotIntervalDuration) {
    recording = true;
    this->replayStorageDuration = replayStorageDuration;
    this->snapshotInterval = snapshotIntervalDuration;
}

void ReplaySystem::stopRecording() {
    recording = false;
}

void ReplaySystem::update(milliseconds deltaTime) {
    if (replayStart) {
        replay();
    } else {
        if (!recording)
            return;

        if (timeElapsedSinceLastSnapshot < snapshotInterval) {
            timeElapsedSinceLastSnapshot += deltaTime;
            return;
        }

        auto snapshot = createEcsDeepSnapshot();
        snapshots.push(std::make_pair(snapshotInterval, std::move(snapshot)));

        totalTimeOfSnapshots += deltaTime;

        if (totalTimeOfSnapshots > replayStorageDuration) {
            snapshots.pop();
            totalTimeOfSnapshots -= snapshotInterval;
        }

        timeElapsedSinceLastSnapshot = 0;
    }
}

void ReplaySystem::replay() {
    if (snapshots.empty()) {
        replayStart = false;
        return;
    }

    while (!snapshots.empty()) {
        if (!replayStart)
            break;

        currentSnapshot = createEcsDeepSnapshot();

        auto snapshot = std::move(snapshots.front());
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(snapshot.first)));
        restore_ecs_snapshot(*snapshot.second);
        auto renderingSystem = SystemManager::getInstance().GetSystem<RenderingSystem>();
        renderingSystem.lock()->update(snapshot.first);
        auto audioSystem = SystemManager::getInstance().GetSystem<AudioSystem>();
        audioSystem.lock()->update(snapshot.first);
        if (snapshot.second != nullptr)
            snapshot.second.reset();

        snapshots.pop();
    }

    replayStart = false;
    restore_ecs_snapshot(*currentSnapshot);
    InputManager::getInstance().clearInputs();
    if (currentSnapshot != nullptr)
        currentSnapshot.reset();

    shouldResetLastTime = true;
}

const std::string ReplaySystem::getName() const {
    return "ReplaySystem";
}

void ReplaySystem::cleanUp() {
    while (!snapshots.empty()) {
        auto snapshot = std::move(snapshots.front());
        if (snapshot.second != nullptr)
            snapshot.second.reset();
        snapshots.pop();
    }

    if (currentSnapshot != nullptr)
        currentSnapshot.reset();
}

std::unique_ptr<ReplaySystem::ECSSnapshot> ReplaySystem::createEcsDeepSnapshot() {
    auto snapshot = std::make_unique<ECSSnapshot>();

    auto &entityManager = EntityManager::getInstance();
    snapshot->entities = entityManager.getAllEntities();
    snapshot->entitiesByName = entityManager.getEntitiesByNameMap();
    snapshot->entitiesByTag = entityManager.getEntitiesByTagMap();
    snapshot->entityStates = entityManager.getStatesForAllEntities();

    auto &componentStore = ComponentStore::GetInstance();
    auto allComponents = componentStore.getComponents();
    for (auto &[type, entityComponents]: allComponents) {
        for (auto &[entityId, component]: entityComponents) {
            snapshot->componentStates[type].emplace(std::make_pair(entityId, std::move(component)));
        }
    }

    auto &behaviorScriptStore = BehaviourScriptStore::getInstance();
    auto scripts = behaviorScriptStore.getAbsolutelyAllBehaviourScripts();
    auto clones = std::vector<std::unique_ptr<IBehaviourScript> >();
    for (auto script: scripts) {
        clones.push_back(std::move(script.get().clone()));
    }

    snapshot->behaviorScripts = std::move(clones);

    return snapshot;
}

void ReplaySystem::restore_ecs_snapshot(const ECSSnapshot &snapshot) {
    EntityManager &entityManager = EntityManager::getInstance();
    entityManager.clearAllEntities();
    for (auto &entity: snapshot.entities) {
        entityManager.addEntity(entity);
    }

    entityManager.setEntitiesByNameMap(snapshot.entitiesByName);
    entityManager.setEntitiesByTagMap(snapshot.entitiesByTag);
    entityManager.setActiveEntities(snapshot.entityStates);

    ComponentStore &componentStore = ComponentStore::GetInstance();
    componentStore.clearComponents();
    for (auto &[type, entityComponents]: snapshot.componentStates) {
        for (auto &[entityId, component]: entityComponents) {
            componentStore.addComponent(entityId, std::move(component->clone()));
        }
    }

    BehaviourScriptStore &behaviorScriptStore = BehaviourScriptStore::getInstance();
    behaviorScriptStore.clearBehaviourScripts();
    for (auto &script: snapshot.behaviorScripts) {
        behaviorScriptStore.addActiveBehaviourScript(script->entityId, std::move(script->clone()));
    }
}

void ReplaySystem::clearCache() {
    replayStart = false;
    snapshots = std::queue<std::pair<float, std::unique_ptr<ECSSnapshot> > >();
    currentSnapshot = nullptr;
    totalTimeOfSnapshots = 0;
    timeElapsedSinceLastSnapshot = 0;
}
