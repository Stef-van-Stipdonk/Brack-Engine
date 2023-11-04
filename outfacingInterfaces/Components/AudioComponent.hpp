//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOCOMPONENT_HPP
#define BRACK_ENGINE_AUDIOCOMPONENT_HPP

#include "IComponent.hpp"
#include <string>

struct AudioComponent : public IComponent {

    explicit AudioComponent(uint32_t entityId) : IComponent(entityId) {}

    ~AudioComponent() = default;

    std::string audioPath;
    bool isLooping, isPlaying;
    float volume;
    int channel;
};

#endif //BRACK_ENGINE_AUDIOCOMPONENT_HPP
