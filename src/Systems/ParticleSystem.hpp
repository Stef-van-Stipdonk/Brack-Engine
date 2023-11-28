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

    void update(int deltaTime) override;

    const std::string getName() const override;

    void cleanUp() override;
};


#endif //BRACK_ENGINE_PARTICLESYSTEM_HPP
