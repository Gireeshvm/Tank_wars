#include"game.h" 

Game::Game(){
}
Game::~Game(){
}

bool Game::init(const char* title, int x, int y, int height, int width, bool fullscreen){
    int flags = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        SDL_Log("Unable to initialize: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
    if(!window){
        SDL_Log("Unable to create Window: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Game::close(){
    SDL_Log("Finishing game!!!");
    SDL_DestroyWindow(window);
    SDL_Quit();
}
