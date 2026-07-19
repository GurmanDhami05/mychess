#include "mygame/game.h"
#include "mygame/move.h"

bool isPlayerPiece(int piece, Turn currentTurn) {
    if (piece == EMPTY) {
        return false;
    }
    if (currentTurn == Turn::White) {
        return piece > 0;
    }
    return piece < 0;
}

bool isEnemyPiece(int fromPiece, int toPiece) {
    return ((fromPiece > 0 && toPiece < 0) || (fromPiece < 0 && toPiece > 0));
}

void switchTurn(Turn &currentTurn) {
    if (currentTurn == Turn::White) {
        currentTurn = Turn::Black;
    } else {
        currentTurn = Turn::White;
    }
}

void movePiece(int board[BOARD_SIZE][BOARD_SIZE], const Move &move) {
    board[move.to.row][move.to.col] = board[move.from.row][move.from.col];
    board[move.from.row][move.from.col] = EMPTY;
}

void undoMove(int board[BOARD_SIZE][BOARD_SIZE],
              const Move &move,
              int capturedPiece) {
    board[move.from.row][move.from.col] = board[move.to.row][move.to.col];
    board[move.to.row][move.to.col] = capturedPiece;
}
