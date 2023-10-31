//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_GAMEENGINE_HPP
#define BRACK_ENGINE_GAMEENGINE_HPP

class RenderWrapper;

class GameEngine {
public:
    GameEngine();

    ~GameEngine();

    bool Initialize();

    void Run();

    void Cleanup();

private:
    RenderWrapper *sdl2Wrapper;
};


#endif //BRACK_ENGINE_GAMEENGINE_HPP
