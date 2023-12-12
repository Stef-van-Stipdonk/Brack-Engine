//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ICOMPONENT_HPP
#define BRACK_ENGINE_ICOMPONENT_HPP

#include <cstdint>
#include <memory>
#include <Entity.hpp>

struct IComponent {
    virtual ~IComponent() {};

    explicit IComponent() {};

    IComponent(const IComponent &other) {
        entityId = other.entityId;
        isActive = other.isActive;
    };

    [[nodiscard]] virtual std::unique_ptr<IComponent> clone() const = 0;


    // Als we nog achter andere overeenkomende dingen komen bij ieder component kunnen we die hier toevoegens
    entity entityId{0};
    bool isActive = true;
};

#endif //BRACK_ENGINE_ICOMPONENT_HPP
