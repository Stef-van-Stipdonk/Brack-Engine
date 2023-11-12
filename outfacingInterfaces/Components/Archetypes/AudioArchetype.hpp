//
// Created by Stef van Stipdonk on 12/11/2023.
//

#ifndef BRACKOCALYPSE_AUDIOARCHETYPE_HPP
#define BRACKOCALYPSE_AUDIOARCHETYPE_HPP

#include <Components/IComponent.hpp>
#include "../../../src/Components/ComponentVisitor.hpp"

class AudioArchetype : public IComponent {
public:
    explicit AudioArchetype() : IComponent() {}

    ~AudioArchetype() override = default;

    void Accept(ComponentVisitor &visitor) override {
        visitor.visit<AudioArchetype>(this);
    }
};

#endif //BRACKOCALYPSE_AUDIOARCHETYPE_HPP
