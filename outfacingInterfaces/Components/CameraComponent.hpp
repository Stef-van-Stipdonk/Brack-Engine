//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CAMERACOMPONENT_HPP
#define BRACK_ENGINE_CAMERACOMPONENT_HPP

#include <memory>
#include "Helpers/Color.hpp"
#include "VelocityComponent.hpp"

struct CameraComponent : public VelocityComponent {
    explicit CameraComponent(uint32_t entityId) : VelocityComponent(entityId) {}

    ~CameraComponent() override = default;

    std::unique_ptr<Vector2> size;
    std::unique_ptr<Color> backgroundColor;
};

#endif //BRACK_ENGINE_CAMERACOMPONENT_HPP
