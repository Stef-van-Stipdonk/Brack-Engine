//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AISYSTEM_HPP
#define BRACK_ENGINE_AISYSTEM_HPP


#include "ISystem.hpp"

class AISystem : public ISystem {
public:
    AISystem();

    ~AISystem() override;

    void Update(float deltaTime) override;
};


#endif //BRACK_ENGINE_AISYSTEM_HPP
