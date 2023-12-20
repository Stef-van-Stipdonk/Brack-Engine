//
// Created by SKIKK on 11/12/2023.
//

#ifndef BRACKOCALYPSE_GRAPHCOMPONENT_HPP
#define BRACKOCALYPSE_GRAPHCOMPONENT_HPP

#include <map>
#include <Helpers/Vector2.hpp>
#include <vector>
#include <Graph/GraphNode.hpp>
#include "IComponent.hpp"

struct GraphComponent : public IComponent {
    explicit GraphComponent() {
    }

    ~GraphComponent() override = default;

    GraphComponent(const GraphComponent &other) : IComponent(other) {
        std::map<GraphNode *, GraphNode *> nodeMap;
        for (const auto &nodePtr: other.graph_) {
            auto newNode = std::make_unique<GraphNode>(*nodePtr);
            nodeMap[nodePtr.get()] = newNode.get();
            graph_.push_back(std::move(newNode));
        }

        for (const auto &nodePtr: graph_) {
            nodePtr->remapEdges(nodeMap);
        }
    }

    std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<GraphComponent>(*this);
    }

    std::vector<std::unique_ptr<GraphNode> > graph_;
};

#endif //BRACKOCALYPSE_GRAPHCOMPONENT_HPP
