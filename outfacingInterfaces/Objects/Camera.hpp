//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CAMERA_HPP
#define BRACK_ENGINE_CAMERA_HPP


#include <memory>
#include <Components/CameraComponent.hpp>
#include "GameObject.hpp"
#include "Helpers/Color.hpp"
#include "Helpers/Vector2.hpp"

class Camera : public GameObject {
public:
    Camera();

    void SetBackgroundColor(const Color color);

    void SetOnScreenPosition(const Vector2 position);

    void SetSize(const Vector2 size);
};


#endif //BRACK_ENGINE_CAMERA_HPP
