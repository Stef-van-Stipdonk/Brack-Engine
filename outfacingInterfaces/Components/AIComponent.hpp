//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AICOMPONENT_HPP
#define BRACK_ENGINE_AICOMPONENT_HPP

#include <cstdint>
#include <Helpers/Vector2.hpp>
#include <Milliseconds.hpp>
#include "IComponent.hpp"

struct AIComponent : public IComponent {

    explicit AIComponent() {}

    ~AIComponent() override = default;

    AIComponent(const AIComponent &other) : IComponent(other) {
        destination = std::make_unique<Vector2>(*other.destination);
        calculatePathInterval = other.calculatePathInterval;
        lastCalculated = other.lastCalculated;
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<AIComponent>(*this);
    }

    std::unique_ptr<Vector2> destination = nullptr;
    std::unique_ptr<Vector2> target = nullptr;
    milliseconds calculatePathInterval = 500;
    milliseconds lastCalculated = 0;
    float speed = 1;
};

#endif //BRACK_ENGINE_AICOMPONENT_HPP
