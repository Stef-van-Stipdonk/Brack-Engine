//
// Created by jesse on 02/11/2023.
//

#include <Components/ObjectInfoComponent.hpp>
#include "BrackEngine.hpp"
#include "Systems/RenderingSystem.hpp"
#include "Logger.hpp"
#include "ConfigSingleton.hpp"
#include "Systems/InputSystem.hpp"
#include "FPSSingleton.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/BehaviourScriptSystem.hpp"
#include "Systems/ClickSystem.hpp"
#include "Systems/AudioSystem.hpp"

BrackEngine::BrackEngine(Config &&config) {
    ConfigSingleton::GetInstance().SetConfig(config);
    SystemManager::GetInstance().AddSystem(std::make_shared<InputSystem>());
    SystemManager::GetInstance().AddSystem(std::make_shared<ClickSystem>());
    SystemManager::GetInstance().AddSystem(std::make_shared<AudioSystem>());
    SystemManager::GetInstance().AddSystem(std::make_shared<BehaviourScriptSystem>());
    SystemManager::GetInstance().AddSystem(std::make_shared<MovementSystem>());
    SystemManager::GetInstance().AddSystem(std::make_shared<RenderingSystem>());

    lastTime = std::chrono::high_resolution_clock::now();

    if (ConfigSingleton::GetInstance().ShowFPS())
        CreateFPS();
}

void BrackEngine::Run() {
    Logger::Debug("Updating systems");
    while (ConfigSingleton::GetInstance().IsRunning()) {
        FPSSingleton::GetInstance().Start();
        SystemManager::GetInstance().UpdateSystems(GetDeltaTime());
        FPSSingleton::GetInstance().End();
//        Logger::Info("FPS: " + std::to_string(FPSSingleton::GetInstance().GetFPS()));
        if (ConfigSingleton::GetInstance().ShowFPS())
            UpdateFPS();
    }

    SystemManager::GetInstance().CleanUp();
}

float BrackEngine::GetDeltaTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(
            currentTime - lastTime);
    lastTime = currentTime;

    float deltaTimeInSeconds = deltaTime.count();
    return deltaTimeInSeconds;

}

void BrackEngine::CreateFPS() {
    auto entityId = EntityManager::GetInstance().CreateEntity();
    auto transformComponent = std::make_unique<TransformComponent>();
    auto objectInfoComponent = std::make_unique<ObjectInfoComponent>();
    auto textComponent = std::make_unique<TextComponent>();

    transformComponent->entityID = entityId;
    objectInfoComponent->entityID = entityId;
    textComponent->entityID = entityId;

    objectInfoComponent->name = "FPS";
    objectInfoComponent->tag = "FPS";

    textComponent->text = "0";
    textComponent->fontSize = 32;
    textComponent->color = std::make_unique<Color>(255, 0, 0, 255);

    ComponentStore::GetInstance().addComponent(entityId, std::move(transformComponent));
    ComponentStore::GetInstance().addComponent(entityId, std::move(objectInfoComponent));
    ComponentStore::GetInstance().addComponent(entityId, std::move(textComponent));
}

void BrackEngine::UpdateFPS() {
    auto &textComponent = ComponentStore::GetInstance().tryGetComponent<TextComponent>(
            1);//TODO ophalen met tag of name van component
    auto fakk = std::to_string(FPSSingleton::GetInstance().GetFPS());

    textComponent.text = fakk;
}
