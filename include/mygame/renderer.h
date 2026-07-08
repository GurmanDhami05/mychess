#pragma once

#include "mygame/constants.h"
#include "mygame/input.h"
#include "mygame/textures.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void drawBoard(SDL_Renderer *renderer, const PieceSelected &selection);

void drawPieces(SDL_Renderer *renderer,
                const Textures &textures,
                const int board[BOARD_SIZE][BOARD_SIZE]);

void render(SDL_Renderer *renderer,
            const Textures &textures,
            const int board[BOARD_SIZE][BOARD_SIZE],
            const PieceSelected &selection);
