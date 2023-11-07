//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOSYSTEM_HPP
#define BRACK_ENGINE_AUDIOSYSTEM_HPP


#include <cstdint>
#include <memory>
#include "ISystem.hpp"
#include "../Wrappers/AudioWrapper.hpp"

class AudioSystem : public ISystem {
public:
    AudioSystem();

    ~AudioSystem() override;

    const std::string GetName() const override;
    void CleanUp() override;

    void Update(float deltaTime) override;

    void PlayAudio(uint32_t entityID, const std::string& audioFilePath);
    void StopAudio(uint32_t entityID);
    void PlayPause(uint32_t entityID);
    void SetVolume(uint32_t entityID, float volume);
    void SetLooping(uint32_t entityID, bool loop);

private:
    std::unique_ptr<AudioWrapper> audioWrapper;
};


#endif //BRACK_ENGINE_AUDIOSYSTEM_HPP
