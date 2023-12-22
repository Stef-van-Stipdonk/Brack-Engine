//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
#define BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP

#include <Milliseconds.hpp>
#include <memory>
#include <vector>
#include <string>
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
        spriteSize = other.spriteSize;
        spriteTileOffset = other.spriteTileOffset;
        spriteMargin = other.spriteMargin;
        spritePath = other.spritePath;
        emitInterval = other.emitInterval;
        untilNextEmit = other.untilNextEmit;
        lifeTime = other.lifeTime;
        activeParticles = other.activeParticles;
        orderInLayer = other.orderInLayer;
        sortingLayer = other.sortingLayer;
        scale = other.scale;
        colliderSize = other.colliderSize;
    }

    std::vector<milliseconds> activeParticles;
    milliseconds emitInterval;
    milliseconds untilNextEmit = 0;

    int maxAmount;
    float speed;
    int sortingLayer;
    int orderInLayer;
    Vector2 spriteSize;
    Vector2 spriteTileOffset;
    Vector2 scale;
    int spriteMargin;
    Vector2 colliderSize;
    std::string spritePath;
    milliseconds lifeTime;
};

#endif //BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
