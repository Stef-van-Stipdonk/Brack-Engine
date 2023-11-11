//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOCOMPONENT_HPP
#define BRACK_ENGINE_AUDIOCOMPONENT_HPP

#include "IComponent.hpp"
#include "../../src/Components/ComponentVisitor.hpp"
#include <string>

struct AudioComponent : public IComponent {
private:
    int channel;

protected:
    explicit AudioComponent(int initialChannel) : channel(initialChannel) {}

public:
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

    int GetChannel() const {
        return channel;
    }
};

#endif //BRACK_ENGINE_AUDIOCOMPONENT_HPP
