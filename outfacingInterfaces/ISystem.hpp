//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ISYSTEM_HPP
#define BRACK_ENGINE_ISYSTEM_HPP

class ISystem {
public:
    virtual ~ISystem() = default;

    // Wordt aangeroepen wanneer het system wordt geadd aan de gameloop, hoeft niet overschreven te worden
    virtual void Init() {}

    // Deze MOET iedere frame of gametick worden aangeroepen
    virtual void Update(float deltaTime) = 0;
};

#endif //BRACK_ENGINE_ISYSTEM_HPP
