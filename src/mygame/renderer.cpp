#include "mygame/renderer.h"
#include "mygame/board.h"
#include "mygame/input.h"

void render(SDL_Renderer *renderer,
            const Textures &textures,
            const int board[BOARD_SIZE][BOARD_SIZE],
            const PieceSelected &selection) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // drawing chess board
    drawBoard(renderer, selection);
    drawPieces(renderer, textures, board);

    SDL_RenderPresent(renderer);
}

void drawBoard(SDL_Renderer *renderer, const PieceSelected &selection) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            bool isSelected = selection.selected && row == selection.row &&
                              col == selection.col;
            if ((row + col) % 2 == 0) {
                if (isSelected) {
                    SDL_SetRenderDrawColor(renderer, 96, 145, 109, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 74, 117, 89, 255);
                }

            } else {

                if (isSelected) {
                    SDL_SetRenderDrawColor(renderer, 255, 235, 156, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255);
                }
            }

            SDL_Rect tile = {
                col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE
            };

            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

void drawPieces(SDL_Renderer *renderer,
                const Textures &textures,
                const int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {

            int piece = board[row][col];

            if (piece == EMPTY) {
                continue;
            }

            SDL_Rect pieceRect = {
                col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE
            };

            SDL_Texture *pieceTexture =
                textures.pieceTextures[pieceToIndex(piece)];

            if (pieceTexture == nullptr) {
                continue;
            }

            SDL_RenderCopy(renderer, pieceTexture, nullptr, &pieceRect);
        }
    }
}
