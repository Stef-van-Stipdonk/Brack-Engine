//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PHYSICSWRAPPER_HPP
#define BRACK_ENGINE_PHYSICSWRAPPER_HPP

#include <box2d/box2d.h>
#include <memory>
#include <vector>
#include <Components/CircleCollisionComponent.hpp>

class PhysicsWrapper {
public:
    PhysicsWrapper() = default;

    ~PhysicsWrapper() = default;

    void Initialize();

    void Update();

    void AddCircles(std::vector<uint32_t> componentIds);

    void Cleanup();

private:
    std::unique_ptr<b2World> world;
    std::unordered_map<uint32_t, std::vector<b2Body *>> bodies;

};


#endif //BRACK_ENGINE_PHYSICSWRAPPER_HPP
