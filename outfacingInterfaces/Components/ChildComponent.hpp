//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_CHILDCOMPONENT_HPP
#define BRACK_ENGINE_CHILDCOMPONENT_HPP

#include <cstdint>
#include <vector>
#include "IComponent.hpp"

struct ChildComponent : public IComponent {
    ChildComponent() = default;

    ~ChildComponent() override = default;

    std::vector<uint32_t> children;
};

#endif //BRACK_ENGINE_CHILDCOMPONENT_HPP
