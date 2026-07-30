#pragma once

#include "chess/chess_engine.h"
#include "chess/game_state.h"
#include "textures.h"
#include "ui_state.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void render(SDL_Renderer *renderer,
            const Textures &textures,
            const ChessEngine &engine,
            const UIState &uiState);

void drawBoard(SDL_Renderer *renderer,
               const GameState &state,
               const UIState &uiState);

void drawPieces(SDL_Renderer *renderer,
                const Textures &textures,
                const Board &board);

void drawLegalMoves(SDL_Renderer *renderer,
                    const GameState &state,
                    const Board &board,
                    const UIState &uiState);
