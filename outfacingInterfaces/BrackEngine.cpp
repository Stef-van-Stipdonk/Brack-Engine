//
// Created by jesse on 02/11/2023.
//

#include "BrackEngine.hpp"
#include "../src/Systems/RenderingSystem.hpp"


void BrackEngine::Update() {
    SystemManager::GetInstance().UpdateSystems(0.0f);//TODO add delta time
}

BrackEngine::BrackEngine() {
    SystemManager::GetInstance().AddSystem(new RenderingSystem());

}
