#include "mygame/renderer.h"
#include "mygame/board.h"
#include "mygame/board_state.h"
#include "mygame/piece_selected.h"
#include <iostream>

void drawFilledCircle(SDL_Renderer *renderer,
                      int centerX,
                      int centerY,
                      int radius)
{
    for (int y = -radius; y <= radius; y++)
    {
        int dx = (int)std::sqrt(radius * radius - y * y);
        SDL_RenderDrawLine(
            renderer, centerX - dx, centerY + y, centerX + dx, centerY + y);
    }
}

void render(SDL_Renderer *renderer,
            const Textures &textures,
            const int board[BOARD_SIZE][BOARD_SIZE],
            const BoardState &state)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // drawing chess board
    drawBoard(renderer, state);
    drawLegalMoves(renderer, state, board);
    drawPieces(renderer, textures, board);

    static bool printed = false;

    if (!printed)
    {
        if (state.checkmate)
        {
            std::cout << "Checkmate!\n";
            printed = true;
        }
        else if (state.stalemate)
        {
            std::cout << "Stalemate!\n";
            printed = true;
        }
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
                    SDL_SetRenderDrawColor(renderer, 196, 70, 70, 255);
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
                    SDL_SetRenderDrawColor(renderer, 196, 70, 70, 255);
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

void drawLegalMoves(SDL_Renderer *renderer,
                    const BoardState &state,
                    const int board[BOARD_SIZE][BOARD_SIZE])
{
    SDL_SetRenderDrawBlendMode(renderer,
                               SDL_BLENDMODE_BLEND); // needed for alpha to work

    for (const Position &pos : state.legalMoves)
    {
        if (board[pos.row][pos.col] == EMPTY)
        {
            SDL_SetRenderDrawColor(renderer, 90, 160, 90, 140);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 220, 60, 60, 140);
        }
        int centerX = pos.col * TILE_SIZE + TILE_SIZE / 2;
        int centerY = pos.row * TILE_SIZE + TILE_SIZE / 2;
        int radius = TILE_SIZE / 6;

        drawFilledCircle(renderer, centerX, centerY, radius);
    }
}
