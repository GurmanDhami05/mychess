#include "mygame/sdl.h"
#include "mygame/constants.h"

#include <iostream>

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed! SDL Error: " << SDL_GetError()
                  << std::endl;
        return false;
    }
    return true;
}

bool initializeSDLImage() {
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_Img initialization failed! SDL Error: "
                  << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Window *createWindow() {
    SDL_Window *window = SDL_CreateWindow("Chess",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          0);

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << std::endl;
        return nullptr;
    }
    return window;
}

SDL_Renderer *createRenderer(SDL_Window *window) {
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "Could not create renderer! SDL Error: " << SDL_GetError()
                  << std::endl;
        return nullptr;
    }

    return renderer;
}

void cleanupSDL(SDL_Renderer *renderer, SDL_Window *window) {

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
