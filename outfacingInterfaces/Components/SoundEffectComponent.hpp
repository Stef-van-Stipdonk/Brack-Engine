//
// Created by Jimmy on 16/11/2023.
//

#ifndef BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP
#define BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP


#include "Archetypes/AudioArchetype.hpp"

struct SoundEffectComponent : public AudioArchetype {
public:
    SoundEffectComponent(std::string path)
            : AudioArchetype(std::move(path), false) {}

    ~SoundEffectComponent() = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<SoundEffectComponent>(*this);
    }

};


#endif //BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP
