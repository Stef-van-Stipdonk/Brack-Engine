//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_INPUTSYSTEM_HPP
#define BRACK_ENGINE_INPUTSYSTEM_HPP


#include <memory>
#include "ISystem.hpp"
#include "../Wrappers/InputWrapper.hpp"

class InputSystem : public ISystem {
public:
    InputSystem();

    ~InputSystem() override;

    void update(milliseconds deltaTime) override;

    const std::string getName() const override;

    InputSystem(const InputSystem &other);

    void cleanUp() override;
    void clearCache() override;

private:
    std::unique_ptr<InputWrapper> inputWrapper;
};


#endif //BRACK_ENGINE_INPUTSYSTEM_HPP
