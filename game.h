#pragma once
#include<vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<string>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 900
#define REFRESH_TIME 1000/60

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
    void drawFps();
    TTF_Font* fpsFont;
    SDL_Color textColor;
    static u_int16_t fpsCounter;
    static uint16_t fps;


private:
    bool isActive = true;
    SDL_Window* window;
    SDL_Texture* texture;
    SDL_TimerID fpsTimer;
};
