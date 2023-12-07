//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
#define BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP

#include <Milliseconds.hpp>
#include <memory>
#include <vector>
#include <Helpers/Color.hpp>
#include <Helpers/Vector2.hpp>
#include "IComponent.hpp"

struct ParticleEmitterComponent : public IComponent {
    explicit ParticleEmitterComponent(int maxAmount) : IComponent(), maxAmount(maxAmount), activeParticles(maxAmount, 0.0) {
    }

    ~ParticleEmitterComponent() override = default;

    virtual std::unique_ptr<IComponent> clone() const override{
        return std::make_unique<ParticleEmitterComponent>(*this);
    }

    ParticleEmitterComponent(const ParticleEmitterComponent& other) : IComponent(other) {
        maxAmount = other.maxAmount;
        speed = other.speed;
        particleSize = other.particleSize;
        emitInterval = other.emitInterval;
        untilNextEmit = other.untilNextEmit;
        lifeTime = other.lifeTime;
        activeParticles = other.activeParticles;
        color = std::make_unique<Color>(*other.color);
        orderInLayer = other.orderInLayer;
        sortingLayer = other.sortingLayer;
    }

    std::vector<milliseconds> activeParticles;
    milliseconds emitInterval;
    milliseconds untilNextEmit = 0;

    int maxAmount;
    float speed;
    int sortingLayer;
    int orderInLayer;
    Vector2 particleSize;
    milliseconds lifeTime;
    std::unique_ptr<Color> color = std::make_unique<Color>(255, 255, 255, 255);
};

#endif //BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
