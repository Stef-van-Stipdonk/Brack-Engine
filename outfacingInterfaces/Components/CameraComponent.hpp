//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CAMERACOMPONENT_HPP
#define BRACK_ENGINE_CAMERACOMPONENT_HPP

#include <memory>
#include "Helpers/Color.hpp"
#include "VelocityComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct CameraComponent : public VelocityComponent {
    explicit CameraComponent() : VelocityComponent() {}

    ~CameraComponent() override = default;

    CameraComponent(const CameraComponent &other) = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    Vector2 size;
    Color backgroundColor;
};

#endif //BRACK_ENGINE_CAMERACOMPONENT_HPP
