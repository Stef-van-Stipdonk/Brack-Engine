//
// Created by SKIKK on 11/12/2023.
//

#include "GraphNodeWrapper.hpp"

GraphNodeWrapper::GraphNodeWrapper(GraphNodeWrapper *previousWrapper, GraphNode& currentNode, float totalWeight, float heuristic) : previousWrapper(previousWrapper), currentNode(currentNode), totalWeight(totalWeight), heuristic(heuristic) {}

bool GraphNodeWrapper::operator<(const GraphNodeWrapper &other) const {
    return (totalWeight + heuristic) > (other.totalWeight + other.heuristic);
}