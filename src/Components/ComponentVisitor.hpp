//
// Created by Olaf van den Berg on 8-11-2023.
//

#ifndef BRACKOCALYPSE_COMPONENTVISITOR_HPP
#define BRACKOCALYPSE_COMPONENTVISITOR_HPP


#include <Components/VelocityComponent.hpp>
#include "IComponentVisitor.hpp"
#include "../includes/ComponentStore.hpp"

class ComponentVisitor : public IComponentVisitor {

public:
    void visit(TransformComponent *component) override;

    void visit(AIComponent *component) override;

    void visit(ObjectInfoComponent *component) override;

    void visit(AnimationComponent *component) override;

    void visit(VelocityComponent *component) override;
};


#endif //BRACKOCALYPSE_COMPONENTVISITOR_HPP
