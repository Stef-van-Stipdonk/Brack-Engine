//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOCOMPONENT_HPP
#define BRACK_ENGINE_AUDIOCOMPONENT_HPP

#include "IComponent.hpp"
#include <string>

struct AudioComponent : public IComponent {

    explicit AudioComponent( ) : IComponent() {}

    ~AudioComponent() override = default;

    std::string audioPath;
    bool isLooping, isPlaying;
    float volume;
    int channel;
};

#endif //BRACK_ENGINE_AUDIOCOMPONENT_HPP
