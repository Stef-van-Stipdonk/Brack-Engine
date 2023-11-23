//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PHYSICSWRAPPER_HPP
#define BRACK_ENGINE_PHYSICSWRAPPER_HPP

#include <memory>
#include <vector>
#include <Components/CircleCollisionComponent.hpp>
#include "box2d/box2d.h"

class ContactListener;

class PhysicsWrapper {
public:

    ~PhysicsWrapper();

    static PhysicsWrapper &getInstance();


    PhysicsWrapper(PhysicsWrapper &other) = delete;

    void operator=(const PhysicsWrapper &) = delete;

    PhysicsWrapper(PhysicsWrapper &&other) = delete;

    void operator=(PhysicsWrapper &&) = delete;

    void Initialize();

    void update(float deltaTime);

    void addCircles(std::vector<uint32_t> componentIds);

    void addBoxes(std::vector<uint32_t> componentIds);


    void Cleanup();

    std::unordered_map<uint32_t, b2Body *> bodies;

private:
    PhysicsWrapper();

    static PhysicsWrapper instance;

    std::unique_ptr<ContactListener> contactListener;

    std::unique_ptr<b2World> world;

    b2BodyType getBodyType(CollisionType collisionType);
};

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact) override;

    void EndContact(b2Contact *contact) override;
};


#endif //BRACK_ENGINE_PHYSICSWRAPPER_HPP
