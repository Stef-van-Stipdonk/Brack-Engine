//
// Created by SKIKK on 11/12/2023.
//

#ifndef BRACKOCALYPSE_GRAPHCOMPONENT_HPP
#define BRACKOCALYPSE_GRAPHCOMPONENT_HPP

#include <Helpers/Vector2.hpp>
#include <vector>
#include <Graph/GraphNode.hpp>
#include "IComponent.hpp"

struct GraphComponent : public IComponent {

    explicit GraphComponent() {}

    ~GraphComponent() override = default;

    GraphComponent(const GraphComponent &other) : IComponent(other) {
        for (auto& nodePtr: graph_) {
            graph_.push_back(std::move(nodePtr));
        }
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<GraphComponent>(*this);
    }

    std::vector<std::unique_ptr<GraphNode>> graph_;
};

#endif //BRACKOCALYPSE_GRAPHCOMPONENT_HPP
