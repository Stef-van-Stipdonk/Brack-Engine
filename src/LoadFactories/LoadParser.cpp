#include "LoadParser.h"
#include "SpriteComponentLoad.h"
#include "TextComponentLoad.h"
#include "CameraComponentLoad.h"

LoadParser LoadParser::instance;

LoadParser &LoadParser::GetInstance() {
    return instance;
}

void LoadParser::AddFactory(std::type_index key, IComponentLoad* componentLoad) {
    auto pair = std::make_pair(key, componentLoad);
    loadFactories.insert(pair);
}

IComponent& LoadParser::Load(std::type_index key) {
    auto& factory = loadFactories[key];
    return *factory->Load();
}

LoadParser::LoadParser() {
    AddFactory(typeid("SpriteComponent"), new SpriteComponentLoad());
    AddFactory(typeid("CameraComponent"), new CameraComponentLoad());
    AddFactory(typeid("TextComponent"), new TextComponentLoad());
}
