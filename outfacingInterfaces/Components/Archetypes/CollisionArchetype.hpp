//
// Created by jesse on 07/12/2023.
//

#ifndef BRACKOCALYPSE_COLLISIONARCHETYPE_HPP
#define BRACKOCALYPSE_COLLISIONARCHETYPE_HPP

#include <Components/IComponent.hpp>
#include <Helpers/Vector2.hpp>
#include <vector>

struct CollisionArchetype : public IComponent {
public:
    explicit CollisionArchetype() : IComponent() {}

    ~CollisionArchetype() override = default;

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<CollisionArchetype>(*this);
    }

    CollisionArchetype(const CollisionArchetype &other) : IComponent(other) {
        collidedWith = other.collidedWith;
    }

    std::unique_ptr<Vector2> offset = std::make_unique<Vector2>(0, 0);
    std::vector<entity> collidedWith;
};

#endif //BRACKOCALYPSE_COLLISIONARCHETYPE_HPP
