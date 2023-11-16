//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLECOMPONENT_HPP
#define BRACK_ENGINE_PARTICLECOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct ParticleComponent : public IComponent {
    explicit ParticleComponent() : IComponent() {}

    ~ParticleComponent() override = default;

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<ParticleComponent>(*this);
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    ParticleComponent(const ParticleComponent& other) : IComponent(other) {
        lifetimeInSeconds = other.lifetimeInSeconds;
    }

    float lifetimeInSeconds;
};


#endif //BRACK_ENGINE_PARTICLECOMPONENT_HPP
