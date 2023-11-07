//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_RENDERINGSYSTEM_HPP
#define BRACK_ENGINE_RENDERINGSYSTEM_HPP


#include <memory>
#include "ISystem.hpp"
#include "../Wrappers/RenderWrapper.hpp"

class RenderingSystem : public ISystem {
public:
    RenderingSystem();

    ~RenderingSystem() override;
    void CleanUp() override;

    const std::string GetName() const override;

    void Update(float deltaTime) override;

private:
    std::unique_ptr<RenderWrapper> sdl2Wrapper;
};


#endif //BRACK_ENGINE_RENDERINGSYSTEM_HPP
