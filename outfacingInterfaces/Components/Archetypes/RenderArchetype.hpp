//
// Created by jesse on 14/11/2023.
//

#ifndef BRACKOCALYPSE_RENDERARCHETYPE_HPP
#define BRACKOCALYPSE_RENDERARCHETYPE_HPP

#include <Components/IComponent.hpp>
#include "../../../src/Components/ComponentVisitor.hpp"


struct RenderArchetype : public IComponent {
public:
    explicit RenderArchetype() : IComponent() {}

    ~RenderArchetype() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<RenderArchetype>(this);
    }

    int sortingLayer, orderInLayer;
};

#endif //BRACKOCALYPSE_RENDERARCHETYPE_HPP
