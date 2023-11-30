//
// Created by SKIKK on 10/11/2023.
//

#ifndef BRACKOCALYPSE_CLICKSYSTEM_HPP
#define BRACKOCALYPSE_CLICKSYSTEM_HPP

#include <Components/ClickableComponent.hpp>
#include "ISystem.hpp"

class ClickSystem : public ISystem {
public:
    ~ClickSystem() override;

    const std::string getName() const override;

    void cleanUp() override;

    void update(milliseconds deltaTime) override;

    ClickSystem();

private:
    void CheckBoxCollision(const ClickableComponent &clickableComponent, const Vector2 &mousePosition);

    void CheckCircleCollision(const ClickableComponent &clickableComponent, const Vector2 &mousePosition);
};


#endif //BRACKOCALYPSE_CLICKSYSTEM_HPP
