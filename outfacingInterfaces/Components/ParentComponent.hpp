//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARENTCOMPONENT_HPP
#define BRACK_ENGINE_PARENTCOMPONENT_HPP

#include "IComponent.hpp"

struct ParentComponent : public IComponent {

    explicit ParentComponent( ) : IComponent() {}

    ~ParentComponent() override = default;

    uint32_t parentID;
};

#endif //BRACK_ENGINE_PARENTCOMPONENT_HPP
