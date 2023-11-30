//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLECOMPONENT_HPP
#define BRACK_ENGINE_PARTICLECOMPONENT_HPP

#include <memory>
#include <Helpers/Color.hpp>
#include <Milliseconds.hpp>
#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"

struct ParticleComponent : public IComponent {
    explicit ParticleComponent() : IComponent() {}

    ~ParticleComponent() override = default;

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<ParticleComponent>(*this);
    }

    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    ParticleComponent(const ParticleComponent& other) : IComponent(other) {
        lifeTime = other.lifeTime;
    }

    milliseconds lifeTime;
};

#endif //BRACK_ENGINE_PARTICLECOMPONENT_HPP
