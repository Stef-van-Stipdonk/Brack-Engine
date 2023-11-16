//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ICOMPONENT_HPP
#define BRACK_ENGINE_ICOMPONENT_HPP

#include <cstdint>
#include <memory>

class ComponentVisitor;

struct IComponent {
    virtual ~IComponent() {};

    explicit IComponent() {};

    IComponent(const IComponent &other) {
        entityID = other.entityID;
        isActive = other.isActive;
    }

    virtual std::unique_ptr<IComponent> clone() const = 0;

    virtual void Accept(ComponentVisitor &visitor) {};


    // Als we nog achter andere overeenkomende dingen komen bij ieder component kunnen we die hier toevoegens
    uint32_t entityID{0};
    bool isActive = true;
};

#endif //BRACK_ENGINE_ICOMPONENT_HPP
