#pragma once

#include "chess/game_state.h"
#include "textures.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void drawBoard(SDL_Renderer *renderer, const GameState &state);

void drawPieces(SDL_Renderer *renderer,
                const Textures &textures,
                const Board &board);

void render(SDL_Renderer *renderer,
            const Textures &textures,
            const Board &board,
            const GameState &state);
void drawLegalMoves(SDL_Renderer *renderer,
                    const GameState &state,
                    const Board &board);
