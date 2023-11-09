//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TRANSFORMCOMPONENT_HPP
#define BRACK_ENGINE_TRANSFORMCOMPONENT_HPP

#include <memory>
#include "IComponent.hpp"
#include "Helpers/Vector2.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct TransformComponent : public IComponent {

    explicit TransformComponent() : IComponent() {}

    ~TransformComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<TransformComponent>(this);
    }

    std::unique_ptr<Vector2> position, scale;
    float rotation;
};

#endif //BRACK_ENGINE_TRANSFORMCOMPONENT_HPP
