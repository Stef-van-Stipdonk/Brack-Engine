//
// Created by Olaf van den Berg on 8-11-2023.
//

#ifndef BRACKOCALYPSE_ICOMPONENTVISITOR_HPP
#define BRACKOCALYPSE_ICOMPONENTVISITOR_HPP

class TransformComponent;

class AIComponent;

class ObjectInfoComponent;

class AnimationComponent;

class VelocityComponent;

class IComponentVisitor {
public:
    virtual void visit(TransformComponent *component) = 0;

    virtual void visit(AIComponent *component) = 0;

    virtual void visit(ObjectInfoComponent *component) = 0;

    virtual void visit(AnimationComponent *component) = 0;

    virtual void visit(VelocityComponent *component) = 0;


};


#endif //BRACKOCALYPSE_ICOMPONENTVISITOR_HPP
