#include"game.h"

int main(){
    Game* game = new Game();

    if(!game->init("Tank Wars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT)){
        SDL_Quit();
        return 1;
    }

    while(game->isRunning()){
        unsigned int frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        uint32_t frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < REFRESH_TIME ) SDL_Delay(REFRESH_TIME - frameTime);
    }
    game->close();

    return 0;
}
