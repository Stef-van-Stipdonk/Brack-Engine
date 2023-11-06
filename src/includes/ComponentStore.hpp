#ifndef SIMPLE_COMPONENTSTORE_HPP
#define SIMPLE_COMPONENTSTORE_HPP

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>

//// Forward declaration of IComponent
//struct IComponent {
//    virtual ~IComponent() = default;
//};

// Simplified ComponentStore
class ComponentStore {
public:
    static ComponentStore &GetInstance() {
        static ComponentStore instance;
        return instance;
    }

    ~ComponentStore() {
        for (auto &pair : components) {
            for (auto &compPair : pair.second) {
                delete compPair.second;
            }
        }
    }

    template<typename T>
    void addComponent(uint32_t entity, T* component) {
        components[typeid(T)][entity] = std::move(component);
    }

    template<typename T>
    T *getComponent(uint32_t entity) {
        auto itType = components.find(typeid(T));
        if (itType != components.end()) {
            auto itEntity = itType->second.find(entity);
            if (itEntity != itType->second.end()) {
                return static_cast<T*>(itEntity->second);
            }
        }
        return nullptr;
    }

    template<typename T>
    void removeComponent(uint32_t entity) {
        auto itType = components.find(typeid(T));
        if (itType != components.end()) {
            delete itType->second[entity];
            itType->second.erase(entity);
        }
    }

private:
    std::unordered_map<std::type_index, std::unordered_map<uint32_t, IComponent*>> components;
};

#endif // SIMPLE_COMPONENTSTORE_HPP
