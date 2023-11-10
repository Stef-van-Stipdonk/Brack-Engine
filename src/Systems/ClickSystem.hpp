//
// Created by SKIKK on 10/11/2023.
//

#ifndef BRACKOCALYPSE_CLICKSYSTEM_HPP
#define BRACKOCALYPSE_CLICKSYSTEM_HPP

#include "ISystem.hpp"

class ClickSystem : public ISystem {
public:
    ~ClickSystem() override;

    const std::string GetName() const override;

    void CleanUp() override;

    void Update(float deltaTime) override;

    ClickSystem();
};


#endif //BRACKOCALYPSE_CLICKSYSTEM_HPP
