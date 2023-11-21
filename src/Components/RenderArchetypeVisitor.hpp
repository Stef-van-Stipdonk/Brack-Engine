//
// Created by jesse on 14/11/2023.
//

#ifndef BRACKOCALYPSE_RENDERARCHETYPEVISITOR_HPP
#define BRACKOCALYPSE_RENDERARCHETYPEVISITOR_HPP

class RenderArchetypeVisitor {
public:
    template<typename T>
    T visit(T *component) {
        return component;
    }
};

#endif //BRACKOCALYPSE_RENDERARCHETYPEVISITOR_HPP
