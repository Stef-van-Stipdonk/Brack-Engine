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
#include <BehaviourScripts/IBehaviourScript.hpp>
#include "../outfacingInterfaces/Milliseconds.hpp"


class ReplaySystem : public ISystem {
public:
    struct ECSSnapshot {
        std::unordered_set<entity> entities;
        std::map<std::string, std::vector<entity>> entitiesByName;
        std::map<std::string, std::vector<entity>> entitiesByTag;

        std::unordered_map<std::type_index, std::unordered_map<entity, std::unique_ptr<IComponent>>> componentStates;
        std::vector<std::unique_ptr<IBehaviourScript>> behaviorScripts;
    };

    ReplaySystem(std::chrono::time_point<std::chrono::high_resolution_clock> &lastTime);

    ~ReplaySystem() override;

    void startRecording(milliseconds replayStorageDuration, milliseconds snapshotIntervalDuration);

    void stopRecording();

    void toggleReplay();

    void update(milliseconds deltaTime) override;;

    void replay();

    const std::string getName() const override;

    void cleanUp() override;

    void clearCache() override;

private:
    std::queue<std::pair<float, std::unique_ptr<ECSSnapshot>>> snapshots;
    std::unique_ptr<ECSSnapshot> currentSnapshot = nullptr;
    milliseconds snapshotInterval;
    milliseconds totalTimeOfSnapshots = 0;
    milliseconds timeElapsedSinceLastSnapshot = 0;
    milliseconds replayStorageDuration;
    bool replayStart = false;
    bool recording;
    std::chrono::time_point<std::chrono::high_resolution_clock> &lastTime;

    std::unique_ptr<ECSSnapshot> createEcsDeepSnapshot();

    static void restore_ecs_snapshot(const ECSSnapshot &snapshot);

};
