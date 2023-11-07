//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TIMERSYSTEM_HPP
#define BRACK_ENGINE_TIMERSYSTEM_HPP


#include "ISystem.hpp"

class TimerSystem : public ISystem {
public:
    TimerSystem();

    ~TimerSystem() override;

    const std::string GetName() const override;
    void CleanUp() override;

    void Update(float deltaTime) override;
};


#endif //BRACK_ENGINE_TIMERSYSTEM_HPP
