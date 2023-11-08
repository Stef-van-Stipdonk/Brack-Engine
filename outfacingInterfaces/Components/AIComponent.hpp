//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AICOMPONENT_HPP
#define BRACK_ENGINE_AICOMPONENT_HPP

#include "../../src/Components/IComponentVisitor.hpp"
#include <cstdint>
#include "IComponent.hpp"

struct AIComponent : public IComponent {

    explicit AIComponent() {}

    ~AIComponent() override = default;

    void Accept(IComponentVisitor &visitor) override {
        visitor.visit(this);
    }

    uint32_t destinationEntityID;
};

#endif //BRACK_ENGINE_AICOMPONENT_HPP
