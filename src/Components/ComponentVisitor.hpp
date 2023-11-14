//
// Created by Olaf van den Berg on 8-11-2023.
//

#ifndef BRACKOCALYPSE_COMPONENTVISITOR_HPP
#define BRACKOCALYPSE_COMPONENTVISITOR_HPP

#include "../includes/ComponentStore.hpp"

class ComponentVisitor {

public:
    template<typename T>
    void visit(T& component) {
        auto componentPtr = std::make_unique<T>(component); // Creating a unique_ptr
        ComponentStore::GetInstance().addComponent(component.entityID, std::move(componentPtr));
    }
};


#endif //BRACKOCALYPSE_COMPONENTVISITOR_HPP
