#include "mygame/check.h"
#include "mygame/game.h"
#include "mygame/position.h"
#include "mygame/rules.h"
#include <stdlib.h>

Position getKingPosition(const int board[BOARD_SIZE][BOARD_SIZE], Turn kingTurn)
{
    int kingPiece = (kingTurn == Turn::White) ? 6 : -6;
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (board[row][col] == kingPiece)
            {
                return { row, col };
            }
        }
    }
    return { -1, -1 }; // Return an invalid position if the king is not found
}

bool isPawnAttack(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    int fromPiece = board[move.from.row][move.from.col];
    int toPiece = board[move.to.row][move.to.col];

    int direction = (fromPiece > 0) ? -1 : 1;

    // Check if the pawn can attack the target square
    if (move.to.row == move.from.row + direction &&
        (move.to.col == move.from.col - 1 || move.to.col == move.from.col + 1))
    {
        return isEnemyPiece(fromPiece, toPiece);
    }

    return false;
}

bool attacksSquare(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{

    int piece = board[move.from.row][move.from.col];
    switch (abs(piece))
    {
    case 1:
        return isPawnAttack(board, move);
    case 2:
        return isRookMove(board, move);
    case 3:
        return isKnightMove(board, move);
    case 4:
        return isBishopMove(board, move);
    case 5:
        return isQueenMove(board, move);
    case 6:
        return isKingMove(board, move);

    default:
        return false;
    }
}

bool isSquareAttacked(const int board[BOARD_SIZE][BOARD_SIZE],
                      const Position &square,
                      Turn attackerTurn)
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            int piece = board[row][col];
            if (piece != EMPTY && isPlayerPiece(piece, attackerTurn))
            {
                Move move{ { row, col }, square };
                if (attacksSquare(board, move))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isKingInCheck(const int board[BOARD_SIZE][BOARD_SIZE], Turn kingTurn)
{
    Position kingPos = getKingPosition(board, kingTurn);
    if (kingPos.row == -1 || kingPos.col == -1)
    {
        return false; // King not found, should not happen in a valid game
    }
    Turn attackerTurn = (kingTurn == Turn::White) ? Turn::Black : Turn::White;
    return isSquareAttacked(board, kingPos, attackerTurn);
}
