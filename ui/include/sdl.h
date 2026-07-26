#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool initializeSDL();
bool initializeSDLImage();

SDL_Window *createWindow();
SDL_Renderer *createRenderer(SDL_Window *window);

void cleanupSDL(SDL_Renderer *renderer, SDL_Window *window);
