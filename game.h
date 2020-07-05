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
    bool loadMedia(SDL_Surface* surface);
    static SDL_Event event;

private:
    bool isActive = true;
    SDL_Window* window;
    SDL_Surface* wSurface ;
};
