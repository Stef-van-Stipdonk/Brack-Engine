#include <string>
#include <vector>
#include <memory>  // For smart pointers
#include <fstream>
#include <tuple>
#include <Helpers/Vector2.hpp>
#include <EngineManagers/InputManager.hpp>
#include "ISystem.hpp"
#include "../includes/ComponentStore.hpp"
#include "../includes/SystemManager.hpp"
#include <queue>


class ReplaySystem : public ISystem {
public:
    struct ECSSnapshot {
        std::unordered_set<entity> entities;
        std::map<std::string, std::vector<entity>> entitiesByName;
        std::map<std::string, std::vector<entity>> entitiesByTag;

        std::unordered_map<std::type_index, std::unordered_map<entity, std::unique_ptr<IComponent>>> componentStates;
    };

    ReplaySystem(int replayStorageDuration, int snapshotInterval = 30);

    ~ReplaySystem() override;;

    void toggleReplay();

    void update(int deltaTime) override;;

    void replay();

    const std::string getName() const override;

    void cleanUp() override;

private:
    std::queue<std::pair<float, std::unique_ptr<ECSSnapshot>>> snapshots;
    std::unique_ptr<ECSSnapshot> currentSnapshot = nullptr;
    int snapshotInterval;
    int totalTimeOfSnapshots = 0;
    int timeElapsedSinceLastSnapshot = 0;
    int replayStorageDuration;
    bool replayStart = false;


    std::unique_ptr<ECSSnapshot> createEcsDeepSnapshot();

    void restore_ecs_snapshot(const ECSSnapshot &snapshot);
};
