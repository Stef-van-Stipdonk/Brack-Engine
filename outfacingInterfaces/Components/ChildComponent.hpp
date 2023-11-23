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

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<ChildComponent>(*this);
    }

    ~ChildComponent() override = default;


    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    ChildComponent(const ChildComponent& other) : IComponent(other){
        children = other.children;
    }

    std::vector<uint32_t> children;
};

#endif //BRACK_ENGINE_CHILDCOMPONENT_HPP
