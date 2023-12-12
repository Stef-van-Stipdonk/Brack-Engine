//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AISYSTEM_HPP
#define BRACK_ENGINE_AISYSTEM_HPP


#include "ISystem.hpp"

class AISystem : public ISystem {
public:
    AISystem();

    ~AISystem() override;

    Vector2 getNextLocation(const std::unique_ptr<Vector2>& target, const std::unique_ptr<Vector2>& source);

    Vector2 calculateVelocity(const std::unique_ptr<Vector2>& target, const std::unique_ptr<Vector2>& source, float speed);

    const std::string getName() const override;

    void cleanUp() override;

    void update(milliseconds deltaTime) override;

    void clearCache() override;
};


#endif //BRACK_ENGINE_AISYSTEM_HPP
