#include <string>
#include <vector>
#include <memory>  // For smart pointers
#include <fstream>
#include <tuple>
#include "ISystem.hpp"
#include "../includes/ComponentStore.hpp"


template<typename... T>
class ReplaySystem : public ISystem {
public:
    struct InputStates {
        std::map<int, InputState> keyInputs;
        std::map<int, InputState> mouseInputs;
        Vector2 mousePosition;
    };

    struct StateSnapshot {
        std::tuple<std::vector<std::shared_ptr<T>>...> componentStates;
        InputStates inputStates;
        float deltaTime;
    };

    struct ECSSnapshot {
        // Entity states
        std::unordered_set<entity> entities;
        std::map<std::string, std::vector<entity>> entitiesByName;
        std::map<std::string, std::vector<entity>> entitiesByTag;

        // Component states
        std::unordered_map<std::type_index, std::unordered_map<entity, std::unique_ptr<IComponent>>> componentStates;

    };

    ReplaySystem(std::string path) : path(path), time(5) {}

    ~ReplaySystem() override {
        file.close();
    };

    void init() override {
        file.open(path);
    }

    void update(float deltaTime) override {
        if (time > 0.0f) {
            time -= deltaTime;
            return;
        }
        time = 5;

        ComponentStore &componentStore = ComponentStore::GetInstance();
        auto components = std::make_tuple(deepCopyComponents(componentStore.getAllComponentsOfType<T>())...);

        InputStates currentInputStates;
        currentInputStates.keyInputs = InputManager::GetInstance().getActiveKeyInputs();
        currentInputStates.mouseInputs = InputManager::GetInstance().getMouseInputs();
        std::unique_ptr<Vector2> &mousePosPtr = InputManager::GetInstance().getMousePositions();
        if (mousePosPtr) {
            currentInputStates.mousePosition = *mousePosPtr;
        }

        StateSnapshot snapshot;
        snapshot.componentStates = components;
        snapshot.inputStates = currentInputStates;
        snapshot.deltaTime = deltaTime;
        snapshots.push_back(snapshot);

        Logger::GetInstance().Debug("ReplaySystem Saved state");
    };

    ECSSnapshot captureSnapshot() {
        ECSSnapshot snapshot;

        EntityManager &entityManager = EntityManager::getInstance();
        snapshot.entities = entityManager.getAllEntities();
        snapshot.entitiesByName = entityManager.getEntitiesByNameMap();
        snapshot.entitiesByTag = entityManager.getEntitiesByTagMap();

        ComponentStore &componentStore = ComponentStore::GetInstance();
        snapshot.componentStates = componentStore.getComponents();

        return snapshot;
    }


    void restoreSnapshot(const ECSSnapshot &snapshot) {
        EntityManager &entityManager = EntityManager::getInstance();
        entityManager.clearAllEntities();
        for (auto &entity: snapshot.entities) {
            entityManager.addEntity(entity, snapshot.entitiesByName[entity], snapshot.entitiesByTag[entity]);
        }
        
        ComponentStore &componentStore = ComponentStore::GetInstance();
        componentStore.clearComponents();
        for (auto &[type, entityComponents]: snapshot.componentStates) {
            for (auto &[entityId, component]: entityComponents) {
                componentStore.addComponent(entityId, *component);
            }
        }
    }


    const std::string getName() const override {
        return "ReplaySystem";
    }

    void cleanUp() override {
    }

    std::ofstream file;
    std::string path;
    std::vector<StateSnapshot> snapshots;
    float time;
private:
    template<typename ComponentType>
    std::vector<std::shared_ptr<ComponentType>> deepCopyComponents(const std::vector<ComponentType *> &components) {
        std::vector<std::shared_ptr<ComponentType>> copiedComponents;
        for (const auto &comp: components) {
            copiedComponents.push_back(std::make_shared<ComponentType>(*comp));
        }
        return copiedComponents;
    }
};
