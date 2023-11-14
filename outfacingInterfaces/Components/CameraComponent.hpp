//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CAMERACOMPONENT_HPP
#define BRACK_ENGINE_CAMERACOMPONENT_HPP

#include <memory>
#include "Helpers/Color.hpp"
#include "VelocityComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"


struct CameraComponent : public IComponent {
    explicit CameraComponent() : IComponent() {}

    ~CameraComponent() override = default;

    CameraComponent(const CameraComponent &other) : IComponent(other) {
        size = std::make_unique<Vector2>(*other.size);
        onScreenPosition = std::make_unique<Vector2>(*other.onScreenPosition);
        backgroundColor = std::make_unique<Color>(*other.backgroundColor);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<CameraComponent>(*this);
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::unique_ptr<Vector2> size = std::make_unique<Vector2>(100, 100);
    std::unique_ptr<Vector2> onScreenPosition = std::make_unique<Vector2>(0, 50);
    std::unique_ptr<Color> backgroundColor = std::make_unique<Color>(0, 0, 0, 255);
};

#endif //BRACK_ENGINE_CAMERACOMPONENT_HPP
