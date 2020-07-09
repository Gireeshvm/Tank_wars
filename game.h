#pragma once
#include<vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 900

class Game{
public:
    Game();
    ~Game();
    bool init(const char* title, int x, int y,int width, int height);
    void handleEvents();
    void update();
    void render();
    void close();
    bool isRunning(){ return isActive;}
    SDL_Texture* loadTexture(char *);
    static SDL_Event event;
    static SDL_Renderer* renderer;

private:
    bool isActive = true;
    SDL_Window* window;
    SDL_Texture* texture;
};
