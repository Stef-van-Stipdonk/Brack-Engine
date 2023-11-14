//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_OBJECTINFOCOMPONENT_HPP
#define BRACK_ENGINE_OBJECTINFOCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include <string>

struct ObjectInfoComponent : public IComponent {

    explicit ObjectInfoComponent() : IComponent() {}

    ~ObjectInfoComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::string name, tag;
    int layer;
    bool isActive = true;
};

#endif //BRACK_ENGINE_OBJECTINFOCOMPONENT_HPP
