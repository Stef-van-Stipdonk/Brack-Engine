//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_INPUTTAG_HPP
#define BRACK_ENGINE_INPUTTAG_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"

struct InputTag : public IComponent {
    explicit InputTag() : IComponent() {}

    ~InputTag() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<InputTag>(this);
    }
};

#endif //BRACK_ENGINE_INPUTTAG_HPP
