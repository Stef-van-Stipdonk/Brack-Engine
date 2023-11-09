//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CHILDCOMPONENT_HPP
#define BRACK_ENGINE_CHILDCOMPONENT_HPP

#include <cstdint>
#include <vector>
#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct ChildComponent : public IComponent {
    explicit ChildComponent() : IComponent() {}

    ~ChildComponent() override = default;


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<ChildComponent>(this);
    }

    std::vector<uint32_t> children;
};

#endif //BRACK_ENGINE_CHILDCOMPONENT_HPP
