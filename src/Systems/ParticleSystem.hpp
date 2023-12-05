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

    void update(milliseconds deltaTime) override;

    const std::string getName() const override;

    void cleanUp() override;

    Vector2 generateRandomDirection(milliseconds speed);
private:
    void updateParticles(milliseconds deltaTime);
    void updateParticleEmitters(milliseconds deltaTime);
};


#endif //BRACK_ENGINE_PARTICLESYSTEM_HPP
