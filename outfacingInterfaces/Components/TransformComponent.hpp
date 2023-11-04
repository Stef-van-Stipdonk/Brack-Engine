//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_TRANSFORMCOMPONENT_HPP
#define BRACK_ENGINE_TRANSFORMCOMPONENT_HPP

#include <memory>
#include "IComponent.hpp"
#include "Helpers/Vector2.hpp"

struct TransformComponent : public IComponent {

    explicit TransformComponent(uint32_t entityId) : IComponent(entityId) {}

    ~TransformComponent() override = default;

    std::unique_ptr<Vector2> position, scale;
    float rotation;
};

#endif //BRACK_ENGINE_TRANSFORMCOMPONENT_HPP
