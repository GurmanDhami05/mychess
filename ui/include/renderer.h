#pragma once

#include "chess/board_state.h"
#include "chess/constants.h"
#include "textures.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void drawBoard(SDL_Renderer *renderer, const BoardState &state);

void drawPieces(SDL_Renderer *renderer,
                const Textures &textures,
                const int board[BOARD_SIZE][BOARD_SIZE]);

void render(SDL_Renderer *renderer,
            const Textures &textures,
            const int board[BOARD_SIZE][BOARD_SIZE],
            const BoardState &state);
void drawLegalMoves(SDL_Renderer *renderer,
                    const BoardState &state,
                    const int board[BOARD_SIZE][BOARD_SIZE]);
