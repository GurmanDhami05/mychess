#pragma once

#include "mygame/board_state.h"
#include "mygame/constants.h"
#include "mygame/move.h"

bool isPlayerPiece(int piece, Turn currentTurn);
void switchTurn(Turn &currentTurn);
void movePiece(int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
bool isEnemyPiece(int fromPiece, int toPiece);
void undoMove(int board[BOARD_SIZE][BOARD_SIZE],
              const Move &move,
              int capturedPiece);
void updateCastlingRights(const Move &move, int movedPiece, BoardState &state);
void performCastle(int board[BOARD_SIZE][BOARD_SIZE], const Move &KingMove);
void undoCastle(int board[BOARD_SIZE][BOARD_SIZE], const Move &KingMove);
void updateEnPassantTarget(const Move &move, int movedPiece, BoardState &state);
void performEnPassant(int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
void undoEnPassant(int board[BOARD_SIZE][BOARD_SIZE],
                   const Move &move,
                   int capturedPawn);
