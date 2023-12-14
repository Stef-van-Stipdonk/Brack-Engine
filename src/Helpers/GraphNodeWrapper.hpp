//
// Created by SKIKK on 11/12/2023.
//

#ifndef BRACKOCALYPSE_GRAPHNODEWRAPPER_HPP
#define BRACKOCALYPSE_GRAPHNODEWRAPPER_HPP


#include <Graph/GraphNode.hpp>

class GraphNodeWrapper {
public:
    GraphNodeWrapper(GraphNodeWrapper* previousWrapper, GraphNode& currentNode, float totalWeight, float heuristic);
    GraphNodeWrapper* previousWrapper;
    GraphNode& currentNode;
    float totalWeight;
    float heuristic;
    bool operator<(const GraphNodeWrapper& other) const;
};


#endif //BRACKOCALYPSE_GRAPHNODEWRAPPER_HPP
