//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PERSISTENCETAG_HPP
#define BRACK_ENGINE_PERSISTENCETAG_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"

struct PersistenceTag : public IComponent {
    explicit PersistenceTag() : IComponent() {}

    ~PersistenceTag() override = default;

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<PersistenceTag>(*this);
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }
};

#endif //BRACK_ENGINE_PERSISTENCETAG_HPP
