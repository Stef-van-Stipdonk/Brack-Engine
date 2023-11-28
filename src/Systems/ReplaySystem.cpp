//
// Created by Stef van Stipdonk on 28/11/2023.
//

#include "ReplaySystem.hpp"
#include "RenderingSystem.hpp"

ReplaySystem::ReplaySystem(int replayStorageDuration, int snapshotInterval) : snapshotInterval(snapshotInterval),
                                                                              replayStorageDuration(
                                                                                      replayStorageDuration) {}

ReplaySystem::~ReplaySystem() {
    cleanUp();
}

void ReplaySystem::toggleReplay() {
    replayStart = !replayStart;
}

void ReplaySystem::update(int deltaTime) {
    if (replayStart) {
        replay();
    }

    if (timeElapsedSinceLastSnapshot < snapshotInterval) {
        timeElapsedSinceLastSnapshot += deltaTime;
        return;
    }

    auto snapshot = createEcsDeepSnapshot();
    snapshots.push(std::make_pair(snapshotInterval, std::move(snapshot)));

    totalTimeOfSnapshots += deltaTime;

    while (totalTimeOfSnapshots > replayStorageDuration) {
        auto toBeDeletedSnapshot = std::move(snapshots.front());
        totalTimeOfSnapshots -= toBeDeletedSnapshot.first;

        if (toBeDeletedSnapshot.second != nullptr)
            toBeDeletedSnapshot.second.reset();

        snapshots.pop();
    }

    timeElapsedSinceLastSnapshot = 0;
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
        auto renderingSystem = SystemManager::GetInstance().GetSystem<RenderingSystem>();
        renderingSystem.lock()->update(snapshot.first);
        if (snapshot.second != nullptr)
            snapshot.second.reset();

        snapshots.pop();
    }

    replayStart = false;
    restore_ecs_snapshot(*currentSnapshot);
    if (currentSnapshot != nullptr)
        currentSnapshot.reset();
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

    auto &componentStore = ComponentStore::GetInstance();
    auto allComponents = componentStore.getComponents();
    for (auto &[type, entityComponents]: allComponents) {
        for (auto &[entityId, component]: entityComponents) {
            snapshot->componentStates[type].emplace(std::make_pair(entityId, std::move(component)));
        }
    }

    return snapshot;
}

void ReplaySystem::restore_ecs_snapshot(const ReplaySystem::ECSSnapshot &snapshot) {
    EntityManager &entityManager = EntityManager::getInstance();
    entityManager.clearAllEntities();
    for (auto &entity: snapshot.entities) {
        entityManager.addEntity(entity);
    }

    entityManager.setEntitiesByNameMap(snapshot.entitiesByName);
    entityManager.setEntitiesByTagMap(snapshot.entitiesByTag);

    ComponentStore &componentStore = ComponentStore::GetInstance();
    componentStore.clearComponents();
    for (auto &[type, entityComponents]: snapshot.componentStates) {
        for (auto &[entityId, component]: entityComponents) {
            componentStore.addComponent(entityId, std::move(component->clone()));
        }
    }
}
