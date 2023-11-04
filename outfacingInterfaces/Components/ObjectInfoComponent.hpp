//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_OBJECTINFOCOMPONENT_HPP
#define BRACK_ENGINE_OBJECTINFOCOMPONENT_HPP

#include "IComponent.hpp"
#include <string>

struct ObjectInfoComponent : public IComponent {

    explicit ObjectInfoComponent(uint32_t entityId) : IComponent(entityId) {}

    ~ObjectInfoComponent() override = default;

    std::string name, tag;
    int layer;
    bool isActive;
};

#endif //BRACK_ENGINE_OBJECTINFOCOMPONENT_HPP
