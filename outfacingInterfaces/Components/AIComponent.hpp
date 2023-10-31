//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AICOMPONENT_HPP
#define BRACK_ENGINE_AICOMPONENT_HPP

#include "IComponent.hpp"
#include <cstdint>

class AIComponent : public IComponent {
public:
    AIComponent() = default;

    ~AIComponent() override = default;

    uint32_t destinationEntityID;
};

#endif //BRACK_ENGINE_AICOMPONENT_HPP
