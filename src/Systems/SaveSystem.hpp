//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_SAVESYSTEM_HPP
#define BRACK_ENGINE_SAVESYSTEM_HPP


#include "ISystem.hpp"

class SaveSystem : public ISystem {
public:
    SaveSystem();

    ~SaveSystem() override;

    void Update(float deltaTime) override;
};


#endif //BRACK_ENGINE_SAVESYSTEM_HPP
