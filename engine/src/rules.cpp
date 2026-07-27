#include "chess/rules.h"
#include "chess/board.h"
#include "chess/check.h"
#include "chess/constants.h"
#include "chess/game.h"
#include "chess/move.h"
#include <cstdlib>

bool isHorizontalOrVertical(const Move &move)
{
    return (move.from.col == move.to.col || move.from.row == move.to.row);
}

bool isPathClear(const Board &board,
                 const Move &move,
                 const int rowStep,
                 const int colStep)
{
    Position current{ move.from.row + rowStep, move.from.col + colStep };

    while (!(current.col == move.to.col && current.row == move.to.row))
    {
        if (board.pieceAt(current) != EMPTY)
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

bool canCastle(const Board &board, const Move &move, const GameState &state)
{
    int piece = board.pieceAt(move.from);
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
            if (board.pieceAt({ homerow, 7 }) != 2)
            {
                return false;
            }
            else if (board.pieceAt({ homerow, 5 }) != EMPTY ||
                     board.pieceAt({ homerow, 6 }) != EMPTY)
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
            if (board.pieceAt({ homerow, 0 }) != 2)
            {
                return false;
            }
            else if (board.pieceAt({ homerow, 3 }) != EMPTY ||
                     board.pieceAt({ homerow, 2 }) != EMPTY ||
                     board.pieceAt({ homerow, 1 }) != EMPTY)
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
            if (board.pieceAt({ homerow, 7 }) != -2)
            {
                return false;
            }
            else if (board.pieceAt({ homerow, 5 }) != EMPTY ||
                     board.pieceAt({ homerow, 6 }) != EMPTY)
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
            if (board.pieceAt({ homerow, 0 }) != -2)
            {
                return false;
            }
            else if (board.pieceAt({ homerow, 3 }) != EMPTY ||
                     board.pieceAt({ homerow, 2 }) != EMPTY ||
                     board.pieceAt({ homerow, 1 }) != EMPTY)
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

bool canEnPassant(const Board &board, const Move &move, const GameState &state)
{
    int fromPiece = board.pieceAt(move.from);
    int toPiece = board.pieceAt(move.to);

    if (abs(fromPiece) != 1)
    {
        return false;
    }

    if (state.enPassantTarget.row == -1 || state.enPassantTarget.col == -1)
    {
        return false;
    }

    if (move.to.row != state.enPassantTarget.row ||
        move.to.col != state.enPassantTarget.col)
    {
        return false;
    }
    if (toPiece != EMPTY)
    {
        return false;
    }

    int direction = (fromPiece > 0) ? -1 : 1;
    if (move.to.row != move.from.row + direction ||
        abs(move.to.col - move.from.col) != 1)
    {
        return false;
    }

    Position capturedPawnPos{ move.from.row, move.to.col };
    int capturedPawn = board.pieceAt(capturedPawnPos);

    if (!isEnemyPiece(fromPiece, capturedPawn) || abs(capturedPawn) != 1)
    {
        return false;
    }

    return true;
}

bool isPawnMove(const Board &board, const Move &move)
{
    int fromPiece = board.pieceAt(move.from);
    int toPiece = board.pieceAt(move.to);

    int direction = (fromPiece > 0) ? -1 : 1;
    int startRow = (fromPiece > 0) ? 6 : 1;

    // one square forward
    if (move.to.row == move.from.row + direction &&
        move.to.col == move.from.col)
    {
        return (board.pieceAt(move.to) == EMPTY);
    }
    // initial two-square forward
    if (move.to.row == move.from.row + 2 * direction &&
        move.to.col == move.from.col)
    {
        return (board.pieceAt(move.to) == EMPTY &&
                board.pieceAt({ move.from.row + direction, move.to.col }) ==
                    EMPTY &&
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

bool isRookMove(const Board &board, const Move &move)
{
    int fromPiece = board.pieceAt(move.from);
    int toPiece = board.pieceAt(move.to);

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
    return (board.pieceAt(move.to) == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isBishopMove(const Board &board, const Move &move)
{

    int fromPiece = board.pieceAt(move.from);
    int toPiece = board.pieceAt(move.to);

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
    return (board.pieceAt(move.to) == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isQueenMove(const Board &board, const Move &move)
{
    return (isRookMove(board, move) || isBishopMove(board, move));
}

bool isKnightMove(const Board &board, const Move &move)
{
    int fromPiece = board.pieceAt(move.from);
    int toPiece = board.pieceAt(move.to);

    int rowDiff = abs(move.to.row - move.from.row);
    int colDiff = abs(move.to.col - move.from.col);

    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
    {
        return false;
    }
    return (board.pieceAt(move.to) == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isKingMove(const Board &board, const Move &move)
{
    int fromPiece = board.pieceAt(move.from);
    int toPiece = board.pieceAt(move.to);

    int rowDiff = abs(move.to.row - move.from.row);
    int colDiff = abs(move.to.col - move.from.col);

    if (!(rowDiff <= 1 && colDiff <= 1))
    {
        return false;
    }

    return (board.pieceAt(move.to) == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isMoveLegal(const Board &board, const Move &move)
{
    int piece = board.pieceAt(move.from);
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
