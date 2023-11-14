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

    CameraComponent(const CameraComponent &other) {
        size = std::make_unique<Vector2>(*other.size);
        backgroundColor = std::make_unique<Color>(*other.backgroundColor);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<CameraComponent>(*this);
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::unique_ptr<Vector2> size;
    std::unique_ptr<Color> backgroundColor;
};

#endif //BRACK_ENGINE_CAMERACOMPONENT_HPP
