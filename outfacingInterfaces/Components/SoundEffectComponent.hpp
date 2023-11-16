//
// Created by Jimmy on 16/11/2023.
//

#ifndef BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP
#define BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP


#include "AudioComponent.hpp"

struct SoundEffectComponent : public AudioComponent {
    SoundEffectComponent(std::string path)
            : AudioComponent(std::move(path), false) {}

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<SoundEffectComponent>(*this);
    }

};


#endif //BRACKOCALYPSE_SOUNDEFFECTCOMPONENT_HPP
