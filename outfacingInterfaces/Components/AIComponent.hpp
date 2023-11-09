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

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<AIComponent>(this);
    }

    uint32_t destinationEntityID;
};

#endif //BRACK_ENGINE_AICOMPONENT_HPP
