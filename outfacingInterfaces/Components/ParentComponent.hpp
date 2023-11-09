//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARENTCOMPONENT_HPP
#define BRACK_ENGINE_PARENTCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct ParentComponent : public IComponent {

    explicit ParentComponent() : IComponent() {}

    ~ParentComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<ParentComponent>(this);
    }

    uint32_t parentID;
};

#endif //BRACK_ENGINE_PARENTCOMPONENT_HPP
