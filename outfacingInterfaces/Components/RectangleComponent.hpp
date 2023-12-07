//
// Created by SKIKK on 14/11/2023.
//

#ifndef BRACKOCALYPSE_RECTANGLECOMPONENT_HPP
#define BRACKOCALYPSE_RECTANGLECOMPONENT_HPP

#include <Helpers/Vector2.hpp>
#include <memory>
#include "Archetypes/RenderArchetype.hpp"
#include "Helpers/Color.hpp"

struct RectangleComponent : public RenderArchetype {
    explicit RectangleComponent(Vector2 size, Color fill)
            : RenderArchetype(), size(std::make_unique<Vector2>(size)), fill(std::make_unique<Color>(fill)) {}

    explicit RectangleComponent(Vector2 size) : RectangleComponent(size, Color(255, 255, 255, 255)) {}

    ~RectangleComponent() override = default;

    RectangleComponent(const RectangleComponent &other) : RenderArchetype(other) {
        size = std::make_unique<Vector2>(*other.size);
        fill = std::make_unique<Color>(*other.fill);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<RectangleComponent>(*this);
    }

    std::unique_ptr<Vector2> size = std::make_unique<Vector2>(0, 0);
    std::unique_ptr<Color> fill = std::make_unique<Color>(0, 0, 0, 255);
};

#endif //BRACKOCALYPSE_RECTANGLECOMPONENT_HPP
