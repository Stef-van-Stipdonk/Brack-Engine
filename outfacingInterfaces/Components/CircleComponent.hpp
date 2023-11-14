//
// Created by SKIKK on 14/11/2023.
//

#ifndef BRACKOCALYPSE_CIRCLECOMPONENT_HPP
#define BRACKOCALYPSE_CIRCLECOMPONENT_HPP

#include <Helpers/Vector2.hpp>
#include <memory>
#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"

struct CircleComponent : public IComponent {
    explicit CircleComponent(float xRadius, float yRadius) : IComponent(), radius(new Vector2(xRadius, yRadius)) {}
    explicit CircleComponent(float radius) : CircleComponent(radius,radius) {}

    ~CircleComponent() override = default;


    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<CircleComponent>(this);
    }

    std::unique_ptr<Vector2> radius;
};

#endif //BRACKOCALYPSE_CIRCLECOMPONENT_HPP
