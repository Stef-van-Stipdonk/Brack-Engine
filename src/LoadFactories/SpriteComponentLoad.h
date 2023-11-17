//
// Created by Stijn Laptop on 16-11-2023.
//

#ifndef BRACKOCALYPSE_SPRITECOMPONENTLOAD_H
#define BRACKOCALYPSE_SPRITECOMPONENTLOAD_H


#include "IComponentLoad.h"

class SpriteComponentLoad : public IComponentLoad {
    std::unique_ptr<IComponent> Load() const;
};


#endif //BRACKOCALYPSE_SPRITECOMPONENTLOAD_H
