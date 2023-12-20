//
// Created by SKIKK on 12/12/2023.
//

#ifndef BRACKOCALYPSE_GRAPHNODE_HPP
#define BRACKOCALYPSE_GRAPHNODE_HPP

#include <map>
#include <Helpers/Vector2.hpp>
#include "GraphEdge.hpp"
#include <vector>

class GraphNode {
public:
    GraphNode(Vector2 position) : position_(position) {
    }

    ~GraphNode() = default;

    GraphNode(const GraphNode &other) : position_(other.position_), visited_(other.visited_) {
        for (const auto &edgePtr: other.edges_) {
            edges_.push_back(std::make_unique<GraphEdge>(*edgePtr));
        }
    }

    void remapEdges(const std::map<GraphNode *, GraphNode *> &nodeMap) {
        for (auto &edgePtr: edges_) {
            edgePtr->remapNodes(nodeMap);
        }
    }

    const bool isVisited() { return visited_; }
    void setVisited(bool visited) { visited_ = visited; };
    Vector2 getPosition() { return position_; }
    void addEdge(std::unique_ptr<GraphEdge> edge) { edges_.push_back(std::move(edge)); }
    const std::vector<std::unique_ptr<GraphEdge> > &getEdges() { return edges_; };

private:
    std::vector<std::unique_ptr<GraphEdge> > edges_;
    Vector2 position_;
    bool visited_ = false;
};
#endif //BRACKOCALYPSE_GRAPHNODE_HPP
