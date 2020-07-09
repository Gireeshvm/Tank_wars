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
SDL_Renderer* Game::renderer;

Game::Game(){
}
Game::~Game(){
}

SDL_Surface* get_surface(char* image){
    SDL_Surface* tmpSurface;
    SDL_Surface* optimized_surface;
    if(!(tmpSurface = IMG_Load(image))) SDL_Log("Couldn't get image surface of %s : %s", image, IMG_GetError()); 
    else if (!(optimized_surface = SDL_ConvertSurface(tmpSurface, tmpSurface->format, 0))) {
        SDL_Log("Couldn't optimize surface %s : %s", image, SDL_GetError());
        SDL_FreeSurface(tmpSurface);
        return optimized_surface;
    }
    return tmpSurface;
}

bool Game::init(const char* title, int x, int y,int width, int height){
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

    if(!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))){
        SDL_Log("Render Creation failed: %s", SDL_GetError());
        return false;
    }
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        SDL_Log("sdl_image initialize failed: %s", IMG_GetError());
        return false;
    }

    images[KS_DEFAULT] = get_surface("../assets/press.bmp");
    images[KS_UP] = get_surface("../assets/up.bmp");
    images[KS_DOWN] = get_surface("../assets/down.bmp");
    images[KS_RIGHT] = get_surface("../assets/right.bmp");
    images[KS_LEFT] = get_surface("../assets/left.bmp");
    current_image = images[KS_DEFAULT];
    return true;
}

void Game::close(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Finishing game!!!");
}

void Game::handleEvents(){
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT) isActive = false;
        else if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
                case SDLK_PERIOD:
                    current_image = images[KS_UP];
                    break;
                case SDLK_e:
                    current_image = images[KS_DOWN];
                    break;
                case SDLK_u:
                    current_image = images[KS_RIGHT];
                    break;
                case SDLK_o:
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
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

void Game::update(){
    texture = loadTexture("../assets/press.bmp");
}

SDL_Texture* Game::loadTexture(char* img){
    SDL_Texture* tmpTexture;
    SDL_Surface* imgSurface = IMG_Load(img);
    if(!imgSurface)SDL_Log("Couldn't loadImage %s : %s ", img, IMG_GetError());
    else{
        tmpTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
        SDL_FreeSurface(imgSurface);
        return tmpTexture;
    }
    return nullptr;
}
