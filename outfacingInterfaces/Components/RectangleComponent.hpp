//
// Created by SKIKK on 14/11/2023.
//

#ifndef BRACKOCALYPSE_RECTANGLECOMPONENT_HPP
#define BRACKOCALYPSE_RECTANGLECOMPONENT_HPP

#include <Helpers/Vector2.hpp>
#include <memory>
#include "IComponent.hpp"
#include "Helpers/Color.hpp"
#include "../../src/Components/ComponentVisitor.hpp"

struct RectangleComponent : public IComponent {
    explicit RectangleComponent(Vector2 size, Color fill) : IComponent(), size(std::make_unique<Vector2>(size)), fill(std::make_unique<Color>(fill)) {}
    explicit RectangleComponent(Vector2 size) : RectangleComponent(size, Color(0,0,0,0)) {}

    ~RectangleComponent() override = default;

    RectangleComponent(const RectangleComponent &other) {
        size = std::make_unique<Vector2>(*other.size);
        fill = std::make_unique<Color>(*other.fill);
        borderWidth = other.borderWidth;
        borderColor = std::make_unique<Color>(*other.borderColor);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<RectangleComponent>(*this);
    }

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<RectangleComponent>(*this);
    }

    std::unique_ptr<Vector2> size;
    std::unique_ptr<Color> fill;
    int borderWidth = 0;
    std::unique_ptr<Color> borderColor = std::make_unique<Color>(0,0,0,0);
};

#endif //BRACKOCALYPSE_RECTANGLECOMPONENT_HPP
