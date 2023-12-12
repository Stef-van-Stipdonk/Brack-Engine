//
// Created by SKIKK on 12/12/2023.
//

#include <Components/GraphComponent.hpp>
#include <Components/TransformComponent.hpp>
#include "Objects/Graph.hpp"

Graph::Graph(Vector2 size, Vector2 nodeCount, Vector2 scale) {
    std::vector<std::vector<std::unique_ptr<GraphNode>>> twoDGrid;
    auto nodeSize = Vector2(size.getX() / nodeCount.getX(),size.getY() / nodeCount.getY());
    for (int y = 0; y < nodeCount.getY(); ++y) {
        twoDGrid.push_back({});
        for (int x = 0; x < nodeCount.getX(); ++x) {
            auto nodeXSize = (nodeSize.getX() * scale.getX());
            auto nodeYSize = (nodeSize.getY() * scale.getY());
            float posX = ((x * nodeXSize) + (nodeXSize / 2)) - (size.getX() / 2);
            float posY = ((y * nodeYSize) + (nodeYSize / 2)) - (size.getY() / 2);
            twoDGrid.back().push_back(std::make_unique<GraphNode>(Vector2(posX,posY)));
        }
    }

    std::vector<std::unique_ptr<GraphNode>> graph;

    for (int y = 0; y < nodeCount.getY(); ++y) {
        for (int x = 0; x < nodeCount.getX(); ++x) {
            auto& node = twoDGrid[y][x];
            if (y - 1 >= 0) {
                auto edge = std::make_unique<GraphEdge>(twoDGrid[y-1][x], node, 1);
                node->addEdge(std::move(edge));
            }

            if (x + 1 < nodeCount.getX()) {
                auto edge = std::make_unique<GraphEdge>(twoDGrid[y][x + 1], node, 1);
                node->addEdge(std::move(edge));
            }

            if (y + 1 < nodeCount.getY()) {
                auto edge = std::make_unique<GraphEdge>(twoDGrid[y+1][x], node, 1);
                node->addEdge(std::move(edge));
            }

            if (x - 1 >= 0) {
                auto edge = std::make_unique<GraphEdge>(twoDGrid[y][x-1], node, 1);
                node->addEdge(std::move(edge));
            }

            graph.push_back(std::move(node));
        }
    }

    initGraph(std::move(graph));
}

Graph::Graph(std::vector<std::unique_ptr<GraphNode>> graph) {
    initGraph(std::move(graph));
}

void Graph::setPosition(Vector2 position) {
    if (entityID == 0) {
        tryGetComponent<TransformComponent>().position = std::make_unique<Vector2>(position);
    } else
        ComponentStore::GetInstance().tryGetComponent<TransformComponent>(entityID).position = std::make_unique<Vector2>(position);
}

void Graph::initGraph(std::vector<std::unique_ptr<GraphNode>> graph) {
    auto graphComponent = std::make_unique<GraphComponent>();
    graphComponent->graph_ = std::move(graph);
    addComponent(std::move(graphComponent));
}