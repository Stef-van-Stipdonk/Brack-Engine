//
// Created by jesse on 17/11/2023.
//

#include "../../includes/ComponentStore.hpp"

ComponentStore ComponentStore::instance;

ComponentStore &ComponentStore::GetInstance() {
    return instance;
}
