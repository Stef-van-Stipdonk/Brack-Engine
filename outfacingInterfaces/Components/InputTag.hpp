//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_INPUTTAG_HPP
#define BRACK_ENGINE_INPUTTAG_HPP

#include "IComponent.hpp"

struct InputTag : public IComponent {
    explicit InputTag(uint32_t entityId) : IComponent(entityId) {}

    ~InputTag() override = default;
};

#endif //BRACK_ENGINE_INPUTTAG_HPP
