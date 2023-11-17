#include <Components/CameraComponent.hpp>
#include "CameraComponentLoad.h"

std::unique_ptr<IComponent> CameraComponentLoad::Load() const {
    return std::make_unique<CameraComponent>();
}
