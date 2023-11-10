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

    std::unique_ptr<Vector2> position = std::make_unique<Vector2>(0.0f, 0.0f);
    std::unique_ptr<Vector2> scale = std::make_unique<Vector2>(1.0f, 1.0f);
    float rotation;
};

#endif //BRACK_ENGINE_TRANSFORMCOMPONENT_HPP
