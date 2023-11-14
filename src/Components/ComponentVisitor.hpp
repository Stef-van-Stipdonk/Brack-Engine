//
// Created by Olaf van den Berg on 8-11-2023.
//

#ifndef BRACKOCALYPSE_COMPONENTVISITOR_HPP
#define BRACKOCALYPSE_COMPONENTVISITOR_HPP

#include "../includes/ComponentStore.hpp"

class ComponentVisitor {

public:
    template<typename T>
    void visit(T *component) {
        ComponentStore::GetInstance().addComponent(component->entityID, component);
    }
};


#endif //BRACKOCALYPSE_COMPONENTVISITOR_HPP
