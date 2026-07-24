#include "mygame/rules.h"
#include "mygame/check.h"
#include "mygame/constants.h"
#include "mygame/game.h"
#include "mygame/move.h"
#include <cstdlib>

bool isHorizontalOrVertical(const Move &move)
{
    return (move.from.col == move.to.col || move.from.row == move.to.row);
}

bool isPathClear(const int board[BOARD_SIZE][BOARD_SIZE],
                 const Move &move,
                 const int rowStep,
                 const int colStep)
{
    Position current{ move.from.row + rowStep, move.from.col + colStep };

    while (!(current.col == move.to.col && current.row == move.to.row))
    {
        if (board[current.row][current.col] != EMPTY)
        {
            return false;
        }
        current.row += rowStep;
        current.col += colStep;
    }
    return true;
}

bool isDiagonal(const Move &move)
{
    int rowDiff = move.to.row - move.from.row;
    int colDiff = move.to.col - move.from.col;
    return (abs(rowDiff) == abs(colDiff));
}

bool canCastle(const int board[BOARD_SIZE][BOARD_SIZE],
               const Move &move,
               const BoardState &state)
{
    int piece = board[move.from.row][move.from.col];
    int homerow = (piece > 0) ? 7 : 0;
    Turn attacker = (piece > 0) ? Turn::Black : Turn::White;

    if (!(move.from.row == move.to.row &&
          abs(move.to.col - move.from.col) == 2))
    {
        return false;
    }
    else if (move.from.row != homerow || move.from.col != 4)
    {
        return false;
    }
    else if (piece > 0)
    {
        if (state.castling.whiteKingMoved)
        {
            return false;
        }
        if (move.to.col == 6 && !state.castling.whiteKingsideRookMoved)
        {
            if (board[homerow][7] != 2)
            {
                return false;
            }
            else if (board[homerow][5] != EMPTY || board[homerow][6] != EMPTY)
            {
                return false;
            }
            else if (isSquareAttacked(board, { homerow, 4 }, attacker) ||
                     isSquareAttacked(board, { homerow, 5 }, attacker) ||
                     isSquareAttacked(board, { homerow, 6 }, attacker))
            {
                return false;
            }
            return true;
        }
        else if (move.to.col == 2 && !state.castling.whiteQueensideRookMoved)
        {
            if (board[homerow][0] != 2)
            {
                return false;
            }
            else if (board[homerow][3] != EMPTY || board[homerow][2] != EMPTY ||
                     board[homerow][1] != EMPTY)
            {
                return false;
            }
            else if (isSquareAttacked(board, { homerow, 4 }, attacker) ||
                     isSquareAttacked(board, { homerow, 3 }, attacker) ||
                     isSquareAttacked(board, { homerow, 2 }, attacker))
            {
                return false;
            }
            return true;
        }
    }
    else if (piece < 0)
    {
        if (state.castling.blackKingMoved)
        {
            return false;
        }
        if (move.to.col == 6 && !state.castling.blackKingsideRookMoved)
        {
            if (board[homerow][7] != -2)
            {
                return false;
            }
            else if (board[homerow][5] != EMPTY || board[homerow][6] != EMPTY)
            {
                return false;
            }
            else if (isSquareAttacked(board, { homerow, 4 }, attacker) ||
                     isSquareAttacked(board, { homerow, 5 }, attacker) ||
                     isSquareAttacked(board, { homerow, 6 }, attacker))
            {
                return false;
            }
            return true;
        }
        else if (move.to.col == 2 && !state.castling.blackQueensideRookMoved)
        {
            if (board[homerow][0] != -2)
            {
                return false;
            }
            else if (board[homerow][3] != EMPTY || board[homerow][2] != EMPTY ||
                     board[homerow][1] != EMPTY)
            {
                return false;
            }
            else if (isSquareAttacked(board, { homerow, 4 }, attacker) ||
                     isSquareAttacked(board, { homerow, 3 }, attacker) ||
                     isSquareAttacked(board, { homerow, 2 }, attacker))
            {
                return false;
            }
            return true;
        }
    }
    return false;
}

bool isPawnMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    int fromPiece = board[move.from.row][move.from.col];
    int toPiece = board[move.to.row][move.to.col];

    int direction = (fromPiece > 0) ? -1 : 1;
    int startRow = (fromPiece > 0) ? 6 : 1;

    // one square forward
    if (move.to.row == move.from.row + direction &&
        move.to.col == move.from.col)
    {
        return (board[move.to.row][move.to.col] == EMPTY);
    }
    // initial two-square forward
    if (move.to.row == move.from.row + 2 * direction &&
        move.to.col == move.from.col)
    {
        return (board[move.to.row][move.to.col] == EMPTY &&
                board[move.from.row + direction][move.to.col] == EMPTY &&
                move.from.row == startRow);
    }
    // diagonal capture
    if (move.to.row == move.from.row + direction &&
        (move.to.col == move.from.col - 1 || move.to.col == move.from.col + 1))
    {
        return (isEnemyPiece(fromPiece, toPiece));
    }

    return false;
}

bool isRookMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    int fromPiece = board[move.from.row][move.from.col];
    int toPiece = board[move.to.row][move.to.col];

    int rowDiff = move.to.row - move.from.row;
    int colDiff = move.to.col - move.from.col;

    int rowStep = ((rowDiff > 0) - (rowDiff < 0));
    int colStep = ((colDiff > 0) - (colDiff < 0));

    if (!isHorizontalOrVertical(move))
    {
        return false;
    }
    if (!isPathClear(board, move, rowStep, colStep))
    {
        return false;
    }
    return (board[move.to.row][move.to.col] == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isBishopMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{

    int fromPiece = board[move.from.row][move.from.col];
    int toPiece = board[move.to.row][move.to.col];

    int rowDiff = move.to.row - move.from.row;
    int colDiff = move.to.col - move.from.col;

    int rowStep = ((rowDiff > 0) - (rowDiff < 0));
    int colStep = ((colDiff > 0) - (colDiff < 0));

    if (!isDiagonal(move))
    {
        return false;
    }
    if (!isPathClear(board, move, rowStep, colStep))
    {
        return false;
    }
    return (board[move.to.row][move.to.col] == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isQueenMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    return (isRookMove(board, move) || isBishopMove(board, move));
}

bool isKnightMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    int fromPiece = board[move.from.row][move.from.col];
    int toPiece = board[move.to.row][move.to.col];

    int rowDiff = abs(move.to.row - move.from.row);
    int colDiff = abs(move.to.col - move.from.col);

    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
    {
        return false;
    }
    return (board[move.to.row][move.to.col] == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isKingMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    int fromPiece = board[move.from.row][move.from.col];
    int toPiece = board[move.to.row][move.to.col];

    int rowDiff = abs(move.to.row - move.from.row);
    int colDiff = abs(move.to.col - move.from.col);

    if (!(rowDiff <= 1 && colDiff <= 1))
    {
        return false;
    }

    return (board[move.to.row][move.to.col] == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isMoveLegal(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    int piece = board[move.from.row][move.from.col];
    switch (abs(piece))
    {
    case 1:
        return isPawnMove(board, move);
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
