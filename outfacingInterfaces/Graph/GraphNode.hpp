//
// Created by SKIKK on 12/12/2023.
//

#ifndef BRACKOCALYPSE_GRAPHNODE_HPP
#define BRACKOCALYPSE_GRAPHNODE_HPP

#include <Helpers/Vector2.hpp>
#include "GraphEdge.hpp"
#include <vector>

class GraphNode {
public:
    GraphNode(Vector2 position) : position_(position) {}
    ~GraphNode() = default;
    GraphNode(const GraphNode& other){
        position_ = other.position_;
        for (auto& edgePtr: edges_) {
            edges_.push_back(std::move(edgePtr));
        }
    }

    const Vector2& getPosition () const { return position_; }
    void addEdge(std::unique_ptr<GraphEdge> edge) { edges_.push_back(std::move(edge)); }
private:
    std::vector<std::unique_ptr<GraphEdge>> edges_;
    Vector2 position_;
};
#endif //BRACKOCALYPSE_GRAPHNODE_HPP
