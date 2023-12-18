//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AISYSTEM_HPP
#define BRACK_ENGINE_AISYSTEM_HPP


#include "ISystem.hpp"

class AISystem : public ISystem {
public:
    AISystem();

    ~AISystem() override;

    Vector2 getNextLocation(Vector2 target, Vector2 source, GraphComponent& graphComponent, TransformComponent& transformGraphComponent);

    Vector2 calculateVelocity(Vector2 target,Vector2 source, float speed);
    void resetGraph(GraphComponent& graphComponent);
    const std::string getName() const override;

    void cleanUp() override;

    void update(milliseconds deltaTime) override;

    void clearCache() override;

    float euclideanDistance(Vector2 a, Vector2 b);

    GraphNode* findClosestNode(Vector2 targetVector, GraphComponent &graphComponent, TransformComponent& transformGraphComponent);
};


#endif //BRACK_ENGINE_AISYSTEM_HPP
