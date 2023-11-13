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

    Color GetBackgroundColor() const;

    void SetBackgroundColor(const Color color);

    Vector2 GetSize() const;

    void SetSize(const Vector2 c_size);

    CameraComponent *GetCameraComponent();

    void SetCameraComponent(CameraComponent *cameraComponent);

private:
    CameraComponent *cameraComponent;
    Vector2 size;
    Color backgroundColor;

};


#endif //BRACK_ENGINE_CAMERA_HPP
