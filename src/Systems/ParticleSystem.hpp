//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PARTICLESYSTEM_HPP
#define BRACK_ENGINE_PARTICLESYSTEM_HPP


#include "ISystem.hpp"

class ParticleSystem : public ISystem {
public:
    ParticleSystem();

    ~ParticleSystem() override;

    void Update(float deltaTime) override;

    const std::string GetName() const override;
    void CleanUp() override;
};


#endif //BRACK_ENGINE_PARTICLESYSTEM_HPP
