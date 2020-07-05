#include"game.h" 

enum KeySurfaces{
    KS_DEFAULT,
    KS_LEFT,
    KS_RIGHT,
    KS_UP,
    KS_DOWN,
    KS_TOTAL
};

SDL_Surface* images[KS_TOTAL];
SDL_Surface* current_image;


SDL_Event Game::event;

Game::Game(){
}
Game::~Game(){
}

SDL_Surface* get_surface(char* image){
    SDL_Surface* tmpSurface;
    SDL_Surface* optimized_surface;
    if(!(tmpSurface = SDL_LoadBMP(image))) SDL_Log("Couldn't get image surface of %s : %s", image, SDL_GetError()); 
    else if (!(optimized_surface = SDL_ConvertSurface(tmpSurface, tmpSurface->format, 0))) {
        SDL_Log("Couldn't optimize surface %s : %s", image, SDL_GetError());
        SDL_FreeSurface(tmpSurface);
        return optimized_surface;
    }
    return tmpSurface;
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
    wSurface = SDL_GetWindowSurface(window);
    images[KS_DEFAULT] = get_surface("../assets/press.bmp");
    images[KS_UP] = get_surface("../assets/up.bmp");
    images[KS_DOWN] = get_surface("../assets/down.bmp");
    images[KS_RIGHT] = get_surface("../assets/right.bmp");
    images[KS_LEFT] = get_surface("../assets/left.bmp");
    current_image = images[KS_DEFAULT];
    return true;
}

void Game::close(){
    SDL_FreeSurface(wSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Finishing game!!!");
}

void Game::handleEvents(){
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT) isActive = false;
        else if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
                case SDLK_UP:
                    current_image = images[KS_UP];
                    break;
                case SDLK_DOWN:
                    current_image = images[KS_DOWN];
                    break;
                case SDLK_RIGHT:
                    current_image = images[KS_RIGHT];
                    break;
                case SDLK_LEFT:
                    current_image = images[KS_LEFT];
                    break;
                default:
                    current_image = images[KS_DEFAULT];
                    break;
            }
        }
    }
}

void Game::render(){
    SDL_UpdateWindowSurface(window);
}

void Game::update(){
        if(!loadMedia(current_image)) SDL_Log("Couldn't Load Image: %s", SDL_GetError());
}

bool Game::loadMedia(SDL_Surface* img){
    if(SDL_BlitSurface(img, NULL, wSurface, NULL) < 0) return false;
    return true;
}
