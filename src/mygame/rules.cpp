#include "mygame/rules.h"
#include "mygame/constants.h"
#include "mygame/game.h"
#include "mygame/move.h"
#include <cstdlib>

bool isHorizontalOrVertical(const Move &move) {
    return (move.fromCol == move.toCol || move.fromRow == move.toRow);
}

bool isPathClear(const int board[BOARD_SIZE][BOARD_SIZE],
                 const Move &move,
                 const int rowStep,
                 const int colStep) {
    int currentRow = move.fromRow + rowStep;
    int currentCol = move.fromCol + colStep;
    while (!(currentCol == move.toCol && currentRow == move.toRow)) {
        if (board[currentRow][currentCol] != EMPTY) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }
    return true;
}

bool isDiagonal(const Move &move) {
    int rowDiff = move.toRow - move.fromRow;
    int colDiff = move.toCol - move.fromCol;
    return (abs(rowDiff) == abs(colDiff));
}

bool isPawnMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    int fromPiece = board[move.fromRow][move.fromCol];
    int toPiece = board[move.toRow][move.toCol];

    int direction = (fromPiece > 0) ? -1 : 1;
    int startRow = (fromPiece > 0) ? 6 : 1;

    // one square forward
    if (move.toRow == move.fromRow + direction && move.toCol == move.fromCol) {
        return (board[move.toRow][move.toCol] == EMPTY);
    }
    // initial two-square forward
    if (move.toRow == move.fromRow + 2 * direction &&
        move.toCol == move.fromCol) {
        return (board[move.toRow][move.toCol] == EMPTY &&
                board[move.fromRow + direction][move.toCol] == EMPTY &&
                move.fromRow == startRow);
    }
    // diagonal capture
    if (move.toRow == move.fromRow + direction &&
        (move.toCol == move.fromCol - 1 || move.toCol == move.fromCol + 1)) {
        return (isEnemyPiece(fromPiece, toPiece));
    }

    return false;
}

bool isRookMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    int fromPiece = board[move.fromRow][move.fromCol];
    int toPiece = board[move.toRow][move.toCol];

    int rowDiff = move.toRow - move.fromRow;
    int colDiff = move.toCol - move.fromCol;

    int rowStep = ((rowDiff > 0) - (rowDiff < 0));
    int colStep = ((colDiff > 0) - (colDiff < 0));

    if (!isHorizontalOrVertical(move)) {
        return false;
    }
    if (!isPathClear(board, move, rowStep, colStep)) {
        return false;
    }
    return (board[move.toRow][move.toCol] == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isBishopMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {

    int fromPiece = board[move.fromRow][move.fromCol];
    int toPiece = board[move.toRow][move.toCol];

    int rowDiff = move.toRow - move.fromRow;
    int colDiff = move.toCol - move.fromCol;

    int rowStep = ((rowDiff > 0) - (rowDiff < 0));
    int colStep = ((colDiff > 0) - (colDiff < 0));

    if (!isDiagonal(move)) {
        return false;
    }
    if (!isPathClear(board, move, rowStep, colStep)) {
        return false;
    }
    return (board[move.toRow][move.toCol] == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isQueenMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    return (isRookMove(board, move) || isBishopMove(board, move));
}

bool isKnightMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    int fromPiece = board[move.fromRow][move.fromCol];
    int toPiece = board[move.toRow][move.toCol];

    int rowDiff = abs(move.toRow - move.fromRow);
    int colDiff = abs(move.toCol - move.fromCol);

    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) {
        return false;
    }
    return (board[move.toRow][move.toCol] == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isKingMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    int fromPiece = board[move.fromRow][move.fromCol];
    int toPiece = board[move.toRow][move.toCol];

    int rowDiff = abs(move.toRow - move.fromRow);
    int colDiff = abs(move.toCol - move.fromCol);

    if (!(rowDiff <= 1 && colDiff <= 1)) {
        return false;
    }

    return (board[move.toRow][move.toCol] == EMPTY ||
            isEnemyPiece(fromPiece, toPiece));
}

bool isMoveLegal(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    int piece = board[move.fromRow][move.fromCol];
    switch (abs(piece)) {
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
