//
// Created by SKIKK on 12/12/2023.
//

#ifndef BRACKOCALYPSE_GRAPH_HPP
#define BRACKOCALYPSE_GRAPH_HPP

#include <vector>
#include <memory>
#include "Graph/GraphNode.hpp"
#include "GameObject.hpp"

class Graph : public GameObject{
public:
    Graph(Vector2 size, Vector2 nodeCount, Vector2 scale);
    Graph(std::vector<std::unique_ptr<GraphNode>> graph);
    void initGraph(std::vector<std::unique_ptr<GraphNode>> graph);
    void setPosition(Vector2 position);
};

#endif //BRACKOCALYPSE_GRAPH_HPP
