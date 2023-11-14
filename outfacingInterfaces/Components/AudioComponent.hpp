//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOCOMPONENT_HPP
#define BRACK_ENGINE_AUDIOCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include <string>

struct AudioComponent : public IComponent {
    explicit AudioComponent() : IComponent() {}

    ~AudioComponent() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<AudioComponent>(this);
    }

    std::string audioPath;
    bool isLooping = false;
    bool isPlaying = false;
    bool shouldBePlaying = false;
    float volume;
    int duration;
    int chnanel;
};

#endif //BRACK_ENGINE_AUDIOCOMPONENT_HPP
