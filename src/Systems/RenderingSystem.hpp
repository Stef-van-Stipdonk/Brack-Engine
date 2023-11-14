//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_RENDERINGSYSTEM_HPP
#define BRACK_ENGINE_RENDERINGSYSTEM_HPP


#include <memory>
#include <set>
#include "ISystem.hpp"
#include "../Wrappers/RenderWrapper.hpp"


struct CompareByLayer {
    bool operator()(const RenderArchetype& lhs, const RenderArchetype& rhs) const {
        if (lhs.sortingLayer == rhs.sortingLayer) {
            return lhs.orderInLayer < rhs.orderInLayer;
        }
        return lhs.sortingLayer < rhs.sortingLayer;
    }
};

class RenderingSystem : public ISystem {
public:
    RenderingSystem();

    ~RenderingSystem() override;

    void CleanUp() override;

    const std::string GetName() const override;

    void Update(float deltaTime) override;

private:
    void SortRenderComponents();

    std::set<RenderArchetype, CompareByLayer> components;
    std::unique_ptr<RenderWrapper> sdl2Wrapper;
};

#endif //BRACK_ENGINE_RENDERINGSYSTEM_HPP
