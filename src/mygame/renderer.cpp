#include "mygame/renderer.h"
#include "mygame/board.h"
#include "mygame/board_state.h"
#include "mygame/piece_selected.h"
#include <iostream>

void render(SDL_Renderer *renderer,
            const Textures &textures,
            const int board[BOARD_SIZE][BOARD_SIZE],
            const BoardState &state)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // drawing chess board
    drawBoard(renderer, state);
    drawPieces(renderer, textures, board);

    if (state.checkmate)
    {
        std::cout << "Checkmate!" << std::endl;
    }
    else if (state.stalemate)
    {
        std::cout << "Stalemate!" << std::endl;
    }

    SDL_RenderPresent(renderer);
}

void drawBoard(SDL_Renderer *renderer, const BoardState &state)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            bool isSelected = state.selection.selected &&
                              row == state.selection.position.row &&
                              col == state.selection.position.col;
            bool isWhiteKingSquare = state.whiteKing.inCheck &&
                                     row == state.whiteKing.position.row &&
                                     col == state.whiteKing.position.col;
            bool isBlackKingSquare = state.blackKing.inCheck &&
                                     row == state.blackKing.position.row &&
                                     col == state.blackKing.position.col;
            bool kingInCheck = isWhiteKingSquare || isBlackKingSquare;
            if ((row + col) % 2 == 0)
            {
                if (kingInCheck)
                {
                    SDL_SetRenderDrawColor(renderer, 170, 82, 82, 255);
                }
                else if (isSelected)
                {
                    SDL_SetRenderDrawColor(renderer, 96, 145, 109, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 74, 117, 89, 255);
                }
            }
            else
            {

                if (kingInCheck)
                {
                    SDL_SetRenderDrawColor(renderer, 170, 82, 82, 255);
                }
                else if (isSelected)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 235, 156, 255);
                }
                else
                {
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
                const int board[BOARD_SIZE][BOARD_SIZE])
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {

            int piece = board[row][col];

            if (piece == EMPTY)
            {
                continue;
            }

            SDL_Rect pieceRect = {
                col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE
            };

            SDL_Texture *pieceTexture =
                textures.pieceTextures[pieceToIndex(piece)];

            if (pieceTexture == nullptr)
            {
                continue;
            }

            SDL_RenderCopy(renderer, pieceTexture, nullptr, &pieceRect);
        }
    }
}
