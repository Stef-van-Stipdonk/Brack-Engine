#ifndef BRACKOCALYPSE_TEXTCOMPONENTLOAD_H
#define BRACKOCALYPSE_TEXTCOMPONENTLOAD_H

#include "IComponentLoad.h"

class TextComponentLoad : public IComponentLoad {
    std::unique_ptr<IComponent> Load() const;
};


#endif //BRACKOCALYPSE_TEXTCOMPONENTLOAD_H
