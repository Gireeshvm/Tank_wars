#pragma once
#include<SDL2/SDL.h>

class Game{
public:
    Game();
    ~Game();
    bool init(const char* title, int x, int y, int height, int width, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void close();
    bool isRunning(){ return isActive;}
private:
    bool isActive;
    SDL_Window* window;
};
