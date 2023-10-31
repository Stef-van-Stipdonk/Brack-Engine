//
// Created by jesse on 30/10/2023.
//

#ifndef BRACK_ENGINE_SDL2WRAPPER_HPP
#define BRACK_ENGINE_SDL2WRAPPER_HPP

#include <iostream>
#include "SDL.h"
#ifdef _WIN32
    #include <windows.h>
#endif

class SDL2Wrapper {
public:
    SDL2Wrapper();
    ~SDL2Wrapper();
    
    bool Initialize();
    void Run();
    void Cleanup();


};


#endif //BRACK_ENGINE_SDL2WRAPPER_HPP
