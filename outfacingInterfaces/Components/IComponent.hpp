//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ICOMPONENT_HPP
#define BRACK_ENGINE_ICOMPONENT_HPP

#include <cstdint>
#include "../../src/Components/IComponentVisitor.hpp"

struct IComponent {
    virtual ~IComponent() = default;

    explicit IComponent() {};

    virtual void Accept(IComponentVisitor &visitor) = 0;


    // Als we nog achter andere overeenkomende dingen komen bij ieder component kunnen we die hier toevoegens
    uint32_t entityID{0};
    bool isActive = true;
};

#endif //BRACK_ENGINE_ICOMPONENT_HPP
