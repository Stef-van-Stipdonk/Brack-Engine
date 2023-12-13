//
// Created by jesse on 31/10/2023.
//

#include "PhysicsWrapper.hpp"
#include "../includes/ComponentStore.hpp"
#include <vector>
#include <algorithm>
#include <Components/CircleCollisionComponent.hpp>
#include <Components/BoxCollisionComponent.hpp>
#include <Components/TransformComponent.hpp>
#include <Components/SpriteComponent.hpp>
#include <Components/VelocityComponent.hpp>
#include <EngineManagers/SceneManager.hpp>

PhysicsWrapper PhysicsWrapper::instance;

PhysicsWrapper::PhysicsWrapper() {
    b2Vec2 gravity(0.0f, 9.8f);
    world = std::make_unique<b2World>(gravity);
    contactListener = std::make_unique<ContactListener>();
    world->SetContactListener(contactListener.get());
}

PhysicsWrapper::~PhysicsWrapper() = default;

PhysicsWrapper &PhysicsWrapper::getInstance() {
    return instance;
}

PhysicsWrapper::PhysicsWrapper(const PhysicsWrapper &other) {
    b2Vec2 gravity(0.0f, 9.8f);
    world = std::make_unique<b2World>(gravity);
    contactListener = std::make_unique<ContactListener>();
}


void PhysicsWrapper::update(milliseconds deltaTime) {
    updateVelocities();
    const int32 velocityIterations{6};
    const int32 positionIterations{2};
    world->Step(deltaTime, velocityIterations, positionIterations);
    updatePositions();
}


void PhysicsWrapper::addCircles(std::vector<entity> componentIds) {
//    circleBodies.insert(circleBodies.end(), componentIds.begin(), componentIds.end());
//
//    if (bodies.find(componentIds.front()) == bodies.end()) {
//        for (auto componentId: componentIds) {
//            auto &circleCollisionComp = ComponentStore::GetInstance().tryGetComponent<CircleCollisionComponent>(
//                    componentId);
//            auto &transformComp = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(componentId);
//            auto &rigidBodyComp = ComponentStore::GetInstance().tryGetComponent<RigidBodyComponent>(componentId);
//            b2BodyDef componentBodyDef;
//            componentBodyDef.position.Set(transformComp.position->getX(), transformComp.position->getY());
//
//            componentBodyDef.type = getBodyType(rigidBodyComp.collisionType);
//
//            b2Body *body = world->CreateBody(&componentBodyDef);
//
//            b2CircleShape shape;
//            shape.m_radius = circleCollisionComp.radius->getX() * transformComp.scale->getX();
//            b2FixtureDef fixtureDef;
//            fixtureDef.isSensor = false;
//            fixtureDef.shape = &shape;
//            fixtureDef.density = 1.0f;
//
//
//            body->CreateFixture(&fixtureDef);
//
//            bodies[componentId] = body;
//
//        }
//    } else {
//        for (auto componentId: componentIds) {
//            auto &transformComp = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(componentId);
//            bodies[componentId]->SetTransform(
//                    b2Vec2(transformComp.position->getX(), transformComp.position->getY()), 0);
//
//        }
//    }
}

void PhysicsWrapper::addBoxes(const std::vector<entity> &componentIds) {
    for (entity id: componentIds) {
        auto &bodyPtr = bodies[id];
        if (bodyPtr.first == nullptr) {
            auto &boxCollisionComponent = ComponentStore::GetInstance().tryGetComponent<BoxCollisionComponent>(
                    id);
            auto &transformComp = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(id);
            auto &rigidBodyComp = ComponentStore::GetInstance().tryGetComponent<RigidBodyComponent>(id);
            b2BodyDef componentBodyDef;
            auto worldPosition = SceneManager::getWorldPosition(transformComp);
            componentBodyDef.position.Set(worldPosition.getX() + boxCollisionComponent.offset->getX(),
                                          worldPosition.getY() + boxCollisionComponent.offset->getY());
            componentBodyDef.type = getBodyType(rigidBodyComp.collisionType);

            bodyPtr.first = world->CreateBody(&componentBodyDef);
            bodyPtr.second = Vector2(boxCollisionComponent.offset->getX(),
                                     boxCollisionComponent.offset->getY());
            bodyPtr.first->SetGravityScale(rigidBodyComp.gravityScale);


            b2PolygonShape shape;
            shape.SetAsBox(boxCollisionComponent.size->getX() * transformComp.scale->getX() / 2,
                           boxCollisionComponent.size->getY() * transformComp.scale->getY() / 2);

            b2FixtureDef fixtureDef;
            fixtureDef.isSensor = boxCollisionComponent.isTrigger;
            fixtureDef.shape = &shape;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = rigidBodyComp.friction;
            fixtureDef.restitution = rigidBodyComp.restitution;

            bodyPtr.first->CreateFixture(&fixtureDef);
        } else {
            auto &transformComp = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(id);
            bodyPtr.first->SetTransform(
                    b2Vec2(transformComp.position->getX() + bodyPtr.second.getX(),
                           transformComp.position->getY() + bodyPtr.second.getY()), 0);
            try {
                auto &velocityComponent = ComponentStore::GetInstance().tryGetComponent<VelocityComponent>(id);
                bodyPtr.first->SetLinearVelocity(
                        b2Vec2(velocityComponent.velocity.getX(), velocityComponent.velocity.getY()));
            } catch (std::exception &e) {
                continue;
            }
        }
    }
}


b2BodyType PhysicsWrapper::getBodyType(CollisionType collisionType) {
    switch (collisionType) {
        case STATIC:
            return b2_staticBody;
        case DYNAMIC:
            return b2_dynamicBody;
        case KINEMATIC:
            return b2_kinematicBody;
        default:
            return b2_staticBody;
    }
}

void PhysicsWrapper::cleanCache() {
//    auto worldBodies = world->GetBodyList();
//    for(int i = 0; i < world->GetBodyCount(); i++)
//    {
////        world->DestroyBody(worldBodies);
//        ++worldBodies;
//    }

    bodies.clear();
}

void PhysicsWrapper::updatePositions() {
    for (auto &body: bodies) {
        auto &transformComp = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(body.first);
        auto position = body.second.first->GetPosition();
        transformComp.position->setX(position.x - body.second.second.getX());
        transformComp.position->setY(position.y - body.second.second.getY());
    }
}

void PhysicsWrapper::updateVelocities() {
    for (auto &body: bodies) {
        try {
            auto &transformComp = ComponentStore::GetInstance().tryGetComponent<VelocityComponent>(body.first);
            body.second.first->SetLinearVelocity(b2Vec2(transformComp.velocity.getX(), transformComp.velocity.getY()));
        } catch (std::exception &e) {
            continue;
        }
    }
}


void ContactListener::BeginContact(b2Contact *contact) {
    std::unordered_map<entity, std::pair<b2Body *, Vector2>> bodies = PhysicsWrapper::getInstance().bodies;
    auto &compStore = ComponentStore::GetInstance();
    auto contactA = contact->GetFixtureA()->GetBody();
    auto contactB = contact->GetFixtureB()->GetBody();
    auto circleEntities = compStore.getEntitiesWithComponent<CircleCollisionComponent>();
    auto boxEntities = compStore.getEntitiesWithComponent<BoxCollisionComponent>();

    entity contactAComponent;
    entity contactBComponent;

    for (auto body: bodies) {
        if (body.second.first == contactA) {
            contactAComponent = body.first;
        }
        if (body.second.first == contactB) {
            contactBComponent = body.first;
        }

    }
    // Add ContactB to ContactA Circle
    if (std::find(circleEntities.begin(), circleEntities.end(), contactAComponent) != circleEntities.end()) {
        compStore.tryGetComponent<CircleCollisionComponent>(contactAComponent).collidedWith.push_back(
                contactBComponent);
    }
    // Add ContactA to ContactB Circle
    if (std::find(circleEntities.begin(), circleEntities.end(), contactBComponent) != circleEntities.end()) {
        compStore.tryGetComponent<CircleCollisionComponent>(contactBComponent).collidedWith.push_back(
                contactAComponent);
    }
    // Add ContactB to ContactA Box
    if (std::find(boxEntities.begin(), boxEntities.end(), contactAComponent) != boxEntities.end()) {
        compStore.tryGetComponent<BoxCollisionComponent>(contactAComponent).collidedWith.push_back(contactBComponent);
    }
    // Add ContactA to ContactB Box
    if (std::find(boxEntities.begin(), boxEntities.end(), contactBComponent) != boxEntities.end()) {
        compStore.tryGetComponent<BoxCollisionComponent>(contactBComponent).collidedWith.push_back(contactAComponent);
    }

}


void ContactListener::EndContact(b2Contact *contact) {
    std::unordered_map<entity, std::pair<b2Body *, Vector2>> bodies = PhysicsWrapper::getInstance().bodies;
    auto &compStore = ComponentStore::GetInstance();
    auto contactA = contact->GetFixtureA()->GetBody();
    auto contactB = contact->GetFixtureB()->GetBody();
    auto circleEntities = compStore.getEntitiesWithComponent<CircleCollisionComponent>();
    auto boxEntities = compStore.getEntitiesWithComponent<BoxCollisionComponent>();

    entity contactAComponent;
    entity contactBComponent;

    for (auto body: bodies) {
        if (body.second.first == contactA) {
            contactAComponent = body.first;
        }
        if (body.second.first == contactB) {
            contactBComponent = body.first;
        }

    }
    if (std::find(circleEntities.begin(), circleEntities.end(), contactAComponent) != circleEntities.end()) {
        auto &component = compStore.tryGetComponent<CircleCollisionComponent>(contactAComponent);
        component.collidedWith.erase(
                std::remove(component.collidedWith.begin(), component.collidedWith.end(), contactBComponent),
                component.collidedWith.end());
    }
    if (std::find(circleEntities.begin(), circleEntities.end(), contactBComponent) != circleEntities.end()) {
        auto &component = compStore.tryGetComponent<CircleCollisionComponent>(contactBComponent);
        component.collidedWith.erase(
                std::remove(component.collidedWith.begin(), component.collidedWith.end(), contactAComponent),
                component.collidedWith.end());
    }
    if (std::find(boxEntities.begin(), boxEntities.end(), contactAComponent) != boxEntities.end()) {
        auto &component = compStore.tryGetComponent<BoxCollisionComponent>(contactAComponent);
        component.collidedWith.erase(
                std::remove(component.collidedWith.begin(), component.collidedWith.end(), contactBComponent),
                component.collidedWith.end());
    }
    if (std::find(boxEntities.begin(), boxEntities.end(), contactBComponent) != boxEntities.end()) {
        auto &component = compStore.tryGetComponent<BoxCollisionComponent>(contactBComponent);
        component.collidedWith.erase(
                std::remove(component.collidedWith.begin(), component.collidedWith.end(), contactAComponent),
                component.collidedWith.end());
    }


}
