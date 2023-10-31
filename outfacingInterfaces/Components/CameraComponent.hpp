//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CAMERACOMPONENT_HPP
#define BRACK_ENGINE_CAMERACOMPONENT_HPP

#include "TransformComponent.hpp"
#include "Helpers/Color.hpp"

class CameraComponent : public TransformComponent {
public:
    CameraComponent() = default;

    ~CameraComponent() override = default;

    Vector2 size;
    Color backgroundColor;
};

#endif //BRACK_ENGINE_CAMERACOMPONENT_HPP
