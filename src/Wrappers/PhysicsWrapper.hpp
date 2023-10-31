//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_PHYSICSWRAPPER_HPP
#define BRACK_ENGINE_PHYSICSWRAPPER_HPP


class PhysicsWrapper {
public:
    PhysicsWrapper();

    ~PhysicsWrapper();

    bool Initialize();

    void Run();

    void Cleanup();
};


#endif //BRACK_ENGINE_PHYSICSWRAPPER_HPP
