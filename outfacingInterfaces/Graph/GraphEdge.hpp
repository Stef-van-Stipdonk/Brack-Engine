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
    GraphEdge(const std::unique_ptr<GraphNode>& to, const std::unique_ptr<GraphNode>& from, float weight) : to_(to), from_(from), weight_(weight) {}
    ~GraphEdge() = default;
    GraphEdge(const GraphEdge& other) : to_(other.to_), from_(other.from_){
        weight_ = other.weight_;
    }
private:
    const std::unique_ptr<GraphNode>& to_;
    const std::unique_ptr<GraphNode>& from_;
    float weight_;
};

#endif //BRACKOCALYPSE_GRAPHEDGE_HPP
