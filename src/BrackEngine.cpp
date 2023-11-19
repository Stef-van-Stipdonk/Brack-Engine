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
#include <typeindex>

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
    auto objectInfoComponent = ObjectInfoComponent();
    auto textComponent = TextComponent();

    objectInfoComponent.name = "FPS";
    objectInfoComponent.tag = "FPS";
    objectInfoComponent.entityID = entityId;

    textComponent.text = "0";
    textComponent.fontSize = 32;
    textComponent.color = std::make_unique<Color>(255, 0, 0, 255);
    textComponent.entityID = entityId;

    ComponentStore::GetInstance().addComponent<TransformComponent>(entityId);
    ComponentStore::GetInstance().addComponent<ObjectInfoComponent>(objectInfoComponent);
    ComponentStore::GetInstance().addComponent<TextComponent>(textComponent);
}

void BrackEngine::UpdateFPS() {
    auto &textComponent = ComponentStore::GetInstance().tryGetComponent<TextComponent>(
            1);//TODO ophalen met tag of name van component
    auto fakk = std::to_string(FPSSingleton::GetInstance().GetFPS());

    textComponent.text = fakk;
}

void BrackEngine::Save(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath, std::ios::binary);

    // Check if the file can be opened for writing
    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing: " << filePath << std::endl;
        return;
    }

    if(!file.write(reinterpret_cast<const char*>(&content), sizeof(std::string))) {
        std::cerr << "Error writing to file: " << filePath << std::endl;
        file.close(); // Close the file before returning
        return;
    }

    file.close();
}

std::string BrackEngine::Load(std::string filePath) {
    std::ifstream file(filePath, std::ios::binary);

    // Check if the file can be opened for reading
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading: " << filePath << std::endl;
        return "";
    }

    std::string content;
    if(!file.read(reinterpret_cast<char*>(&content), sizeof(std::string))) {
        return "";
    }

    file.close();
    return content;
}