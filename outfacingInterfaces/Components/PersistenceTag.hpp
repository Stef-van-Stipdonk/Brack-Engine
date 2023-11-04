//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PERSISTENCETAG_HPP
#define BRACK_ENGINE_PERSISTENCETAG_HPP

#include "IComponent.hpp"

struct PersistenceTag : public IComponent {
    explicit PersistenceTag(uint32_t entityId) : IComponent(entityId) {}

    ~PersistenceTag() override = default;
};

#endif //BRACK_ENGINE_PERSISTENCETAG_HPP
