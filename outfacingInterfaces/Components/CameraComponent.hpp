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


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<CameraComponent>(this);
    }
    
    std::unique_ptr<Vector2> size = std::make_unique<Vector2>(100, 100);
    std::unique_ptr<Vector2> onScreenPosition = std::make_unique<Vector2>(0, 0);
    std::unique_ptr<Color> backgroundColor = std::make_unique<Color>(0, 0, 0, 255);
};

#endif //BRACK_ENGINE_CAMERACOMPONENT_HPP
