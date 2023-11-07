//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_REPLAYSYSTEM_HPP
#define BRACK_ENGINE_REPLAYSYSTEM_HPP


#include <string>
#include "ISystem.hpp"

class ReplaySystem : public ISystem {
public:
    ReplaySystem();

    ~ReplaySystem() override;

    void Update(float deltaTime) override;

    std::string GetName() override;
    void CleanUp() override;

    std::string path;
    bool isReplaying;
private:
    void SaveReplay();

    void LoadReplay();
};


#endif //BRACK_ENGINE_REPLAYSYSTEM_HPP
