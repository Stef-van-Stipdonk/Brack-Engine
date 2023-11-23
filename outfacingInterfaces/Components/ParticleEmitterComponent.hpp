//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
#define BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"

struct ParticleEmitterComponent : public IComponent {
    explicit ParticleEmitterComponent() : IComponent() {}

    ~ParticleEmitterComponent() override = default;

    virtual std::unique_ptr<IComponent> clone() const override{
        return std::make_unique<ParticleEmitterComponent>(*this);
    }


    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    ParticleEmitterComponent(const ParticleEmitterComponent& other) : IComponent(other) {
        amount = other.amount;
    }

    int amount;
};


#endif //BRACK_ENGINE_PARTICLEEMITTERCOMPONENT_HPP
