//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARENTCOMPONENT_HPP
#define BRACK_ENGINE_PARENTCOMPONENT_HPP

#include "IComponent.hpp"

class ParentComponent : public IComponent {
public:
    ParentComponent() = default;

    ~ParentComponent() override = default;

    const uint32_t parentID;
};

#endif //BRACK_ENGINE_PARENTCOMPONENT_HPP
