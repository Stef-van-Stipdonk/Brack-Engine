//
// Created by jesse on 31/10/2023.
//

#include "PhysicsWrapper.hpp"
#include <vector>
#include <Components/CircleCollisionComponent.hpp>

PhysicsWrapper PhysicsWrapper::instance;

PhysicsWrapper::PhysicsWrapper() {
    b2Vec2 gravity(0.0f, -9.8f);
    world = std::make_unique<b2World>(gravity);
    contactListener = std::make_unique<ContactListener>();
    world->SetContactListener(contactListener.get());
}

PhysicsWrapper::~PhysicsWrapper() = default;

PhysicsWrapper &PhysicsWrapper::GetInstance() {
    return instance;
}

void PhysicsWrapper::Initialize() {

}

void PhysicsWrapper::update() {
    const float timeStep{1.0f / 60.0f};
    const int32 velocityIterations{6};
    const int32 positionIterations{2};

    world->Step(timeStep, velocityIterations, positionIterations);

}


void PhysicsWrapper::addCircles(std::vector<uint32_t> componentIds) {

//    Check if Entity is already in bodies
    if (bodies.find(componentIds.front()) == bodies.end()) {
        for (auto componentId: componentIds) {
            auto &circleCollisionComp = ComponentStore::GetInstance().tryGetComponent<CircleCollisionComponent>(
                    componentId);
            auto &transformComp = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(componentId);
            b2BodyDef componentBodyDef;
            componentBodyDef.position.Set(transformComp.position->getX(), transformComp.position->getY());
            componentBodyDef.type = getBodyType(circleCollisionComp.collisionType);

            b2Body *body = world->CreateBody(&componentBodyDef);

            b2CircleShape shape;
            shape.m_radius = circleCollisionComp.radius->getX();
            b2FixtureDef fixtureDef;
            fixtureDef.isSensor = true;
            fixtureDef.shape = &shape;
            fixtureDef.density = 1.0f;


            body->CreateFixture(&fixtureDef);

            bodies[componentId].push_back(body);

        }
    } else {
        for (auto componentId: componentIds) {
            auto &transformComp = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(componentId);
            bodies[componentId].front()->SetTransform(
                    b2Vec2(transformComp.position->getX(), transformComp.position->getY()), 0);

        }
    }
}

void PhysicsWrapper::Cleanup() {

}

b2BodyType PhysicsWrapper::getBodyType(CollisionType collisionType) {
    switch (collisionType) {
        case STATIC:
            return b2_staticBody;
        case DYNAMIC:
            return b2_dynamicBody;
        case KINEMATIC:
            return b2_kinematicBody;
    }
}


void ContactListener::BeginContact(b2Contact *contact) {
    std::unordered_map<uint32_t, std::vector<b2Body *>> bodies = PhysicsWrapper::GetInstance().bodies;
    auto &compStore = ComponentStore::GetInstance();
    auto contactA = contact->GetFixtureA()->GetBody();
    auto contactB = contact->GetFixtureB()->GetBody();


    for (auto &body: bodies) {
        if (body.second.front() == contactA) {
            auto &circleCollisionComp = compStore.tryGetComponent<CircleCollisionComponent>(
                    body.first);

            Logger::GetInstance().Info("Collision with " + std::to_string(body.first));
        } else if (body.second.front() == contactB) {
            auto &circleCollisionComp = compStore.tryGetComponent<CircleCollisionComponent>(
                    body.first);

            Logger::GetInstance().Info("Collision with " + std::to_string(body.first));
        }
    }
}

void ContactListener::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
}
