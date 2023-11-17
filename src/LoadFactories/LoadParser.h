#ifndef BRACKOCALYPSE_LOADPARSER_H
#define BRACKOCALYPSE_LOADPARSER_H

#include <map>
#include <string>
#include <typeindex>
#include "IComponentLoad.h"

class LoadParser {
public:
    static LoadParser &GetInstance();

    ~LoadParser() = default;

    LoadParser(const LoadParser &) = delete;

    LoadParser &operator=(const LoadParser &) = delete;

    LoadParser(LoadParser &&) = delete;

    LoadParser &operator=(LoadParser &&) = delete;

    void AddFactory(std::type_index key, IComponentLoad* componentLoad);
    IComponent& Load(std::type_index key);
private:
    LoadParser();

    std::map<std::type_index, IComponentLoad*> loadFactories;
    static LoadParser instance;
};


#endif //BRACKOCALYPSE_LOADPARSER_H
