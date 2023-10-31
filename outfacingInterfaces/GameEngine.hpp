//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_GAMEENGINE_HPP
#define BRACK_ENGINE_GAMEENGINE_HPP

class SDL2Wrapper;

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    bool Initialize();
    void Run();
    void Cleanup();
private:
    SDL2Wrapper* sdl2Wrapper;
};


#endif //BRACK_ENGINE_GAMEENGINE_HPP
