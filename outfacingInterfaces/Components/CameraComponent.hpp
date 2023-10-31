//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CAMERACOMPONENT_HPP
#define BRACK_ENGINE_CAMERACOMPONENT_HPP

#include <memory>
#include "TransformComponent.hpp"
#include "Helpers/Color.hpp"

struct CameraComponent : public TransformComponent {
    CameraComponent() = default;

    ~CameraComponent() override = default;

    std::unique_ptr<Vector2> size;
    std::unique_ptr<Color> backgroundColor;
};

#endif //BRACK_ENGINE_CAMERACOMPONENT_HPP
