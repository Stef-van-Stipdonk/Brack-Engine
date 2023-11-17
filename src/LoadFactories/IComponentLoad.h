#ifndef BRACKOCALYPSE_ICOMPONENTLOAD_H
#define BRACKOCALYPSE_ICOMPONENTLOAD_H

#include <Components/IComponent.hpp>

class IComponentLoad {
public:
    virtual std::unique_ptr<IComponent> Load() const = 0;
};

#endif //BRACKOCALYPSE_ICOMPONENTLOAD_H
