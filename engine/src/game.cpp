#include "chess/game.h"
#include "chess/game_state.h"
#include "chess/move.h"
#include <cstdlib>

bool isPlayerPiece(int piece, Turn currentTurn)
{
    if (piece == EMPTY)
    {
        return false;
    }
    if (currentTurn == Turn::White)
    {
        return piece > 0;
    }
    return piece < 0;
}

bool isEnemyPiece(int fromPiece, int toPiece)
{
    return ((fromPiece > 0 && toPiece < 0) || (fromPiece < 0 && toPiece > 0));
}

void switchTurn(Turn &currentTurn)
{
    if (currentTurn == Turn::White)
    {
        currentTurn = Turn::Black;
    }
    else
    {
        currentTurn = Turn::White;
    }
}

void updateCastlingRights(const Move &move, int movedPiece, GameState &state)
{
    if (movedPiece == 2 && move.from.row == 7 &&
        move.from.col == 0) // White queen-side rook
    {
        state.castling.whiteQueensideRookMoved = true;
    }
    else if (movedPiece == 2 && move.from.row == 7 &&
             move.from.col == 7) // White king-side rook
    {
        state.castling.whiteKingsideRookMoved = true;
    }
    else if (movedPiece == -2 && move.from.row == 0 &&
             move.from.col == 0) // Black queen-side rook
    {
        state.castling.blackQueensideRookMoved = true;
    }
    else if (movedPiece == -2 && move.from.row == 0 &&
             move.from.col == 7) // Black king-side rook
    {
        state.castling.blackKingsideRookMoved = true;
    }

    if (movedPiece == 6) // White king
    {
        state.castling.whiteKingMoved = true;
    }
    else if (movedPiece == -6) // Black king
    {
        state.castling.blackKingMoved = true;
    }
}

void updateEnPassantTarget(const Move &move, int movedPiece, GameState &state)
{
    if (abs(movedPiece) == 1 && abs(move.to.row - move.from.row) == 2)
    {
        state.enPassantTarget.row = (move.from.row + move.to.row) / 2;
        state.enPassantTarget.col = move.from.col;
    }
    else
    {
        state.enPassantTarget = { -1, -1 };
    }
}
