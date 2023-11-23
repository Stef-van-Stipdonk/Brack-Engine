//
// Created by Stef van Stipdonk on 12/11/2023.
//

#ifndef BRACKOCALYPSE_AUDIOARCHETYPE_HPP
#define BRACKOCALYPSE_AUDIOARCHETYPE_HPP

#include <Components/IComponent.hpp>
#include "../../../src/Components/ComponentVisitor.hpp"

struct AudioArchetype : public IComponent {
public:
    explicit AudioArchetype() : IComponent() {}

    ~AudioArchetype() override = default;

    virtual std::unique_ptr<IComponent> clone() const override {
        return std::make_unique<AudioArchetype>(*this);
    }

    AudioArchetype(const AudioArchetype &other) : IComponent(other) {}

    void accept(ComponentVisitor &visitor) override {
        visitor.visit(*this);
    }
};

#endif //BRACKOCALYPSE_AUDIOARCHETYPE_HPP
