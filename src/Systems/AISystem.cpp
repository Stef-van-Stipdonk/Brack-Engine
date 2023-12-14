//
// Created by jesse on 31/10/2023.
//

#include <Helpers/Vector2.hpp>
#include <Components/AIComponent.hpp>
#include <Components/TransformComponent.hpp>
#include <Components/VelocityComponent.hpp>
#include <Components/GraphComponent.hpp>
#include <queue>
#include "AISystem.hpp"
#include "../includes/ComponentStore.hpp"
#include "../Helpers/GraphNodeWrapper.hpp"

struct GraphNodePtrCompare {
    bool operator()(const GraphNodeWrapper* a, const GraphNodeWrapper* b) const {
        return *a < *b;
    }
};

AISystem::AISystem() {

}

AISystem::~AISystem() {

}

void AISystem::update(milliseconds deltaTime) {
    auto aiComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<AIComponent>();
    for (auto& aiComponentId: aiComponentIds) {
        auto& aiComponent = ComponentStore::GetInstance().tryGetComponent<AIComponent>(aiComponentId);
        auto& aiTransformComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(aiComponentId);
        auto& velocityComponent = ComponentStore::GetInstance().tryGetComponent<VelocityComponent>(aiComponentId);

        if(aiComponent.nextDestination != nullptr && aiComponent.lastCalculated > 0){
            aiComponent.lastCalculated -= deltaTime;
        }

        if(aiComponent.target != nullptr && (aiComponent.nextDestination == aiTransformComponent.position || aiComponent.lastCalculated <= 0)){
            auto graphComponentId = ComponentStore::GetInstance().getEntitiesWithComponent<GraphComponent>()[0];
            auto& graphComponent = ComponentStore::GetInstance().tryGetComponent<GraphComponent>(graphComponentId);
            auto& transformGraphComponent = ComponentStore::GetInstance().tryGetComponent<TransformComponent>(graphComponentId);
            resetGraph(graphComponent);
            aiComponent.lastCalculated = aiComponent.calculatePathInterval;
            aiComponent.nextDestination = std::make_unique<Vector2>(getNextLocation(*aiComponent.target, *aiTransformComponent.position, graphComponent, transformGraphComponent));
        }

        auto newVelocity = calculateVelocity(aiComponent.nextDestination, aiTransformComponent.position, aiComponent.speed);
        if(velocityComponent.velocity != newVelocity){
            velocityComponent.velocity = newVelocity;
        }
    }
}

void AISystem::resetGraph(GraphComponent &graphComponent) {
    for (auto& node: graphComponent.graph_) {
        node->setVisited(false);
    }
}

Vector2 AISystem::calculateVelocity(const std::unique_ptr<Vector2> &target, const std::unique_ptr<Vector2> &source,
                                    float speed) {
    // Calculate the direction vector
    float dx = target->getX() - source->getX();
    float dy = target->getY() - source->getY();

    // Calculate the length of the direction vector
    float length = std::sqrt(dx * dx + dy * dy);

    // Normalize the direction vector to get a unit vector
    float unit_vector_x = dx / length;
    float unit_vector_y = dy / length;

    // Calculate the velocity vector
    float velocity_x = unit_vector_x * speed;
    float velocity_y = unit_vector_y * speed;

    return {velocity_x, velocity_y};
}

float AISystem::euclideanDistance(Vector2 a, Vector2 b) {
    return std::sqrt(std::pow(a.getX() - b.getX(), 2) + std::pow(a.getY() - b.getY(), 2));
}

// Function to find the vector closest to the target vector
GraphNode* AISystem::findClosestNode(Vector2 targetVector, GraphComponent& graphComponent, TransformComponent& transformGraphComponent) {
    float minDistance = std::numeric_limits<float>::max();
    GraphNode* closestNode = nullptr;

    for (auto& node : graphComponent.graph_) {
        float distance = euclideanDistance(targetVector, node->getPosition() + *transformGraphComponent.position);
        if (distance < minDistance) {
            // Update the minimum distance and set the closest node
            minDistance = distance;
            closestNode = node.get();
        }
    }

    return closestNode;
}

Vector2 AISystem::getNextLocation(Vector2 targetPosition, Vector2 sourcePosition, GraphComponent& graphComponent, TransformComponent& transformGraphComponent) {
    std::priority_queue<GraphNodeWrapper*,std::vector<GraphNodeWrapper*>, GraphNodePtrCompare> toBeVisited{};
    targetPosition += *transformGraphComponent.position;
    auto closestToTarget = findClosestNode(targetPosition, graphComponent, transformGraphComponent);
    auto closestToSource = findClosestNode(sourcePosition, graphComponent, transformGraphComponent);
    float heuristic = sqrt(pow(closestToTarget->getPosition().getX() - closestToSource->getPosition().getX() , 2) + pow(closestToTarget->getPosition().getY() - closestToSource->getPosition().getY(), 2));
    toBeVisited.push(new GraphNodeWrapper(nullptr, *closestToTarget, 0.0f, heuristic));

    while(!toBeVisited.empty()){
        GraphNodeWrapper* currentWrapper = toBeVisited.top();
        toBeVisited.pop();
        if(currentWrapper->currentNode.isVisited()){
            continue;
        }

        // When target node is found, is always shortest path as well because the smallest is being taken from toBeVisited
        if(currentWrapper->currentNode.getPosition() == closestToSource->getPosition()){
            if(currentWrapper->previousWrapper){
                return currentWrapper->previousWrapper->currentNode.getPosition();
            }else{
                return currentWrapper->currentNode.getPosition();
            }
        }

        // Visit node, look at edges and add them to toBeVisited
        for (auto& edge: currentWrapper->currentNode.getEdges()) {
            if(!edge->getTo().isVisited()){
                float heuristic = sqrt(pow(closestToSource->getPosition().getX() - edge->getTo().getPosition().getX() , 2) + pow(closestToSource->getPosition().getY() - edge->getTo().getPosition().getY(), 2));
                float toTotalWeight =  edge->getWeight() + currentWrapper->totalWeight;

                toBeVisited.push(new GraphNodeWrapper(currentWrapper, edge->getTo(), toTotalWeight, heuristic));
            }
        }
        // Tag currentNode as visited and remove it from toBeVisited
        currentWrapper->currentNode.setVisited(true);
    }
}

const std::string AISystem::getName() const {
    return "AISystem";
}

void AISystem::cleanUp() {

}

void AISystem::clearCache() {

}
