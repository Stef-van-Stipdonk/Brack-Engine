//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CHILDCOMPONENT_HPP
#define BRACK_ENGINE_CHILDCOMPONENT_HPP

#include <cstdint>
#include <vector>
#include "IComponent.hpp"

struct ChildComponent : public IComponent {
    explicit ChildComponent(uint32_t entityId) : IComponent(entityId) {}

    ~ChildComponent() override = default;

    std::vector<uint32_t> children;
};

#endif //BRACK_ENGINE_CHILDCOMPONENT_HPP
