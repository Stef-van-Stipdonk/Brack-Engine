
#include "../../includes/ComponentStore.hpp"

ComponentStore ComponentStore::instance;

ComponentStore &ComponentStore::GetInstance() {
    return instance;
}
