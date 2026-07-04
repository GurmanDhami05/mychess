#pragma once

#include <SDL2/SDL.h>
#include <array>

struct Textures {
    std::array<SDL_Texture *, 13> pieceTextures;
};

void loadTextures(Textures &textures, SDL_Renderer *renderer);

bool checkTexture(const Textures &textures);

void destroyTextures(Textures &textures);
