#include "mygame/rules.h"
#include "mygame/constants.h"
#include "mygame/move.h"
#include <cstdlib>

bool isPawnMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    int piece = board[move.fromRow][move.fromCol];
    // white pawn
    if (piece > 0) {
        // one square forward
        if (move.toRow == move.fromRow - 1 && move.toCol == move.fromCol) {
            return (board[move.toRow][move.toCol] == EMPTY);
        }
        // initial two-square forward
        if (move.toRow == move.fromRow - 2 && move.toCol == move.fromCol) {
            return (board[move.toRow][move.toCol] == EMPTY &&
                    board[move.fromRow - 1][move.toCol] == EMPTY &&
                    move.fromRow == 6);
        }
        // diagonal capture
        if (move.toRow == move.fromRow - 1 &&
            (move.toCol == move.fromCol - 1 ||
             move.toCol == move.fromCol + 1)) {
            return (board[move.toRow][move.toCol] < 0);
        }

        // black pawn
    } else if (piece < 0) {
        // one square forward
        if (move.toRow == move.fromRow + 1 && move.toCol == move.fromCol) {
            return (board[move.toRow][move.toCol] == EMPTY);
        }
        // initial two-square forward
        if (move.toRow == move.fromRow + 2 && move.toCol == move.fromCol) {
            return (board[move.toRow][move.toCol] == EMPTY &&
                    board[move.fromRow + 1][move.toCol] == EMPTY &&
                    move.fromRow == 1);
        }
        // diagonal capture
        if (move.toRow == move.fromRow + 1 &&
            (move.toCol == move.fromCol - 1 ||
             move.toCol == move.fromCol + 1)) {
            return (board[move.toRow][move.toCol] > 0);
        }
    }
    return false;
}

bool isMoveLegal(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    int piece = board[move.fromRow][move.fromCol];
    switch (abs(piece)) {
    case 1:
        return isPawnMove(board, move);
        // case 2:
        //     return isRookMove(board, move);
        //
        // case 3:
        //     return isKnightMove(board, move);
        //
        // case 4:
        //     return isBishopMove(board, move);
        //
        // case 5:
        //     return isQueenMove(board, move);
        //
        // case 6:
        //     return isKingMove(board, move);

    default:
        return false;
    }
}
