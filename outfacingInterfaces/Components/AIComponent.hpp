//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AICOMPONENT_HPP
#define BRACK_ENGINE_AICOMPONENT_HPP

#include <cstdint>
#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"

struct AIComponent : public IComponent {

    explicit AIComponent() {}

    ~AIComponent() override = default;

    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    AIComponent(const AIComponent& other) : IComponent(other){
        destinationEntityID = other.destinationEntityID;
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<AIComponent>(*this);
    }

    uint32_t destinationEntityID;
};

#endif //BRACK_ENGINE_AICOMPONENT_HPP
