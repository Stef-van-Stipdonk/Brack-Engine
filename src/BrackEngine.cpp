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
        Logger::Info("FPS: " + std::to_string(FPSSingleton::GetInstance().GetFPS()));
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
    auto& textComponent = ComponentStore::GetInstance().tryGetComponent<TextComponent>(1);
    auto fakk = std::to_string(FPSSingleton::GetInstance().GetFPS());

    textComponent.text = fakk;
}

void BrackEngine::Save(std::string filePath) {
    std::ofstream file(filePath, std::ios::binary);

    // Check if the file can be opened for writing
    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing: " << filePath << std::endl;
        return;
    }

    // Write components to file
    const std::unordered_map<std::type_index, std::unordered_map<uint32_t, std::unique_ptr<IComponent>>>& components = ComponentStore::GetInstance().getComponents();

    for (const auto& typeIndexMapPair : components) {
        for (const auto& entityIdComponentPair : typeIndexMapPair.second) {
            // Serialize the data of each component individually
            const std::unique_ptr<IComponent>& component = entityIdComponentPair.second;
            if (!(file.write(reinterpret_cast<const char*>(&typeIndexMapPair.first), sizeof(std::type_index)) &&
                  file.write(reinterpret_cast<const char*>(&entityIdComponentPair.first), sizeof(uint32_t)) &&
                  file.write(reinterpret_cast<const char*>(component.get()), sizeof(IComponent)))) {
                std::cerr << "Error writing to file: " << filePath << std::endl;
                file.close(); // Close the file before returning
                return;
            }
        }
    }

    file.close();
}

void BrackEngine::Load(std::string filePath) {
    std::ifstream file(filePath, std::ios::binary);

    // Check if the file can be opened for reading
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading: " << filePath << std::endl;
        return;
    }

    // Map to store the deserialized components
    std::unordered_map<std::type_index, std::unordered_map<uint32_t, std::unique_ptr<IComponent>>> deserializedComponents;

    while (true) {
        std::type_index typeIndex = typeid("");
        uint32_t entityId;

        // Read the typeIndex, entityId, and component data
        if (!(file.read(reinterpret_cast<char*>(&typeIndex), sizeof(typeIndex)) &&
              file.read(reinterpret_cast<char*>(&entityId), sizeof(entityId)))) {
            // Break if unable to read more data
            break;
        }

        // Create an instance of the component (polymorphic type assumed)
        std::unique_ptr<IComponent> component;
        LoadParser::GetInstance().Load(typeIndex);

        // Read the component data
        if (!(file.read(reinterpret_cast<char*>(component.get()), sizeof(IComponent)))) {
            std::cerr << "Error reading component data from file: " << filePath << std::endl;
            return;
        }

//        ComponentStore::GetInstance().addComponent(entityId, std::move(component));
    }

    file.close();
}