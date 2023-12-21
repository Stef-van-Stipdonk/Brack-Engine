//
// Created by SKIKK on 12/12/2023.
//

#ifndef BRACKOCALYPSE_GRAPHEDGE_HPP
#define BRACKOCALYPSE_GRAPHEDGE_HPP

#include "GraphNode.hpp"
#include <memory>

class GraphNode;

class GraphEdge {
public:
    GraphEdge(GraphNode *to, GraphNode *from, float weight) : to_(to), from_(from), weight_(weight) {
    }

    ~GraphEdge() = default;

    GraphEdge(const GraphEdge &other) : to_(other.to_), from_(other.from_), weight_(other.weight_) {
    }

    void remapNodes(const std::map<GraphNode *, GraphNode *> &nodeMap) {
        to_ = nodeMap.at(to_);
        from_ = nodeMap.at(from_);
    }

    GraphNode &getTo() { return *to_; }
    float getWeight() { return weight_; }

private:
    GraphNode *to_;
    GraphNode *from_;
    float weight_;
};

#endif //BRACKOCALYPSE_GRAPHEDGE_HPP
