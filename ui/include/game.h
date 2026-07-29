#pragma once

#include "chess/chess_engine.h"
#include "textures.h"
#include <SDL2/SDL.h>

class Game
{
  private:
    ChessEngine engine_;

    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;

    Textures textures_;

    bool running_ = true;
    SDL_Event event_;

    void handleEvents();
    void renderFrame();
    void cleanup();

  public:
    bool initialize();
    void run();

    ~Game();
};
