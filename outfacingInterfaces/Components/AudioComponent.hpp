//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOCOMPONENT_HPP
#define BRACK_ENGINE_AUDIOCOMPONENT_HPP

#include "IComponent.hpp"
#include <string>

class AudioComponent : public IComponent {
public:
    AudioComponent() = default;

    ~AudioComponent() = default;

    std::string audioPath;
    bool isLooping, isPlaying;
    float volume;
    int channel;
};

#endif //BRACK_ENGINE_AUDIOCOMPONENT_HPP
