#include"game.h"

int main(){
    Game* game = new Game();

    if(!game->init("Tank Wars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 800,false)){
        SDL_Quit();
        return 1;
    }
    SDL_Delay(5000);

    game->close();

    return 0;
}
