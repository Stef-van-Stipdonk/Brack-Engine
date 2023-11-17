//
// Created by Stijn Laptop on 16-11-2023.
//

#ifndef BRACKOCALYPSE_CAMERACOMPONENTLOAD_H
#define BRACKOCALYPSE_CAMERACOMPONENTLOAD_H


#include "IComponentLoad.h"

class CameraComponentLoad : public IComponentLoad {
    std::unique_ptr<IComponent> Load() const;
};


#endif
