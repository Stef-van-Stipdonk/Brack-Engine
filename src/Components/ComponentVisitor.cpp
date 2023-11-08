//
// Created by Olaf van den Berg on 8-11-2023.
//

#include "ComponentVisitor.hpp"
#include "../../outfacingInterfaces/Components/TransformComponent.hpp"
#include "../../outfacingInterfaces/Components/ObjectInfoComponent.hpp"
#include "../../outfacingInterfaces/Components/AIComponent.hpp"
#include "../../outfacingInterfaces/Components/AnimationComponent.hpp"
#include "../../outfacingInterfaces/Components/VelocityComponent.hpp"


void ComponentVisitor::visit(TransformComponent *component) {
    ComponentStore::GetInstance().addComponent(component->entityID, component);
}

void ComponentVisitor::visit(VelocityComponent *component) {
    ComponentStore::GetInstance().addComponent(component->entityID, component);
}

void ComponentVisitor::visit(AIComponent *component) {
    ComponentStore::GetInstance().addComponent(component->entityID, component);
}

void ComponentVisitor::visit(ObjectInfoComponent *component) {
    ComponentStore::GetInstance().addComponent(component->entityID, component);
}

void ComponentVisitor::visit(AnimationComponent *component) {
    ComponentStore::GetInstance().addComponent(component->entityID, component);
}