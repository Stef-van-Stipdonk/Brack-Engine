//
// Created by jesse on 31/10/2023.
//

#include "PhysicsWrapper.hpp"
#include "ContactListener.hpp"
#include <vector>
#include <Components/CircleCollisionComponent.hpp>


PhysicsWrapper::PhysicsWrapper() {
    b2Vec2 gravity(0.0f, -9.8f);
    world = std::make_unique<b2World>(gravity);
    contactListener = std::make_unique<ContactListener>();
    world->SetContactListener(contactListener.get());
}

PhysicsWrapper::~PhysicsWrapper() {}


void PhysicsWrapper::Initialize() {

}

void PhysicsWrapper::Update() {
    const float timeStep{1.0f / 60.0f};
    const int32 velocityIterations{6};
    const int32 positionIterations{2};

    world->Step(timeStep, velocityIterations, positionIterations);

}


void PhysicsWrapper::AddCircles(std::vector<uint32_t> componentIds) {

//    Check if Entity is already in bodies
    if (bodies.find(componentIds.front()) == bodies.end()) {
        for (auto componentId: componentIds) {
            auto &circleCollisionComp = ComponentStore::GetInstance().tryGetComponent<CircleCollisionComponent>(
                    componentId);
            auto &transformComp = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(componentId);
            b2BodyDef componentBodyDef;
            componentBodyDef.position.Set(transformComp.position->getX(), transformComp.position->getY());
            componentBodyDef.type = b2_dynamicBody;
            b2Body *body = world->CreateBody(&componentBodyDef);

            b2CircleShape shape;
            shape.m_radius = circleCollisionComp.radius->getX();
            b2FixtureDef fixtureDef;
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


