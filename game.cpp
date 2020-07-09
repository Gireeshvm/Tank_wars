#include"game.h" 

SDL_Event Game::event;
SDL_Renderer* Game::renderer;
uint16_t Game::fps ;
uint16_t Game::fpsCounter = 0;

Game::Game(){
}
Game::~Game(){
}

uint32_t fpsMeter(uint32_t interval, void* params);

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
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS)<0){
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
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        SDL_Log("sdl_image initialize failed: %s", IMG_GetError());
        return false;
    }


    if( TTF_Init() < 0 ) {
        SDL_Log("Couldn't initialize ttf library : %s", TTF_GetError());
        return false;
    }

    fpsFont = TTF_OpenFont("../assets/roboto.ttf", 50);
    if(!fpsFont) SDL_Log("Couldn't load fonts : %s", TTF_GetError());
    textColor = {0, 0xFF, 0};
    fpsTimer =  SDL_AddTimer(1000, fpsMeter, NULL);

    return true;
}

void Game::close(){
    SDL_RemoveTimer(fpsTimer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Finishing game!!!");
}

void Game::handleEvents(){
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT) isActive = false;
    }
}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture,NULL,NULL);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
    for(int i= 100; i < SCREEN_HEIGHT; i+=3) SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, i);
    drawFps();
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

void Game::update(){
    texture = loadTexture("../assets/press.bmp");
    fpsCounter++;
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

uint32_t fpsMeter(uint32_t interval, void* params){
    Game::fps = Game::fpsCounter;
    Game::fpsCounter = 0;
    return 1000;
}


void Game::drawFps(){
    SDL_Rect fpsRect = {SCREEN_WIDTH - 32, 0, 32, 32};
    std::string fpsString = std::to_string(fps);
    SDL_Surface* texSurface = TTF_RenderUTF8_Solid(fpsFont, fpsString.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, texSurface);
    SDL_FreeSurface(texSurface);
    SDL_RenderCopy(renderer,textTexture, NULL, &fpsRect);

}
