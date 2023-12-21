//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP

#include <memory>
#include "Archetypes/CollisionArchetype.hpp"
#include "Helpers/Vector2.hpp"


struct BoxCollisionComponent : public CollisionArchetype {
    explicit BoxCollisionComponent(Vector2 size) : CollisionArchetype(), size(std::make_unique<Vector2>(size)) {}


    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<BoxCollisionComponent>(*this);
    }

    ~BoxCollisionComponent() override {
        size = nullptr;
    };

    BoxCollisionComponent(const BoxCollisionComponent &other) : CollisionArchetype(other) {
        if (other.size != nullptr)
            size = std::make_unique<Vector2>(*other.size);
    }


    std::unique_ptr<Vector2> size;

};

#endif //BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
