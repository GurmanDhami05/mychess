#pragma once

#include "mygame/board_state.h"
#include "mygame/constants.h"
#include "mygame/move.h"

bool isMoveLegal(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);

bool isPawnMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
bool isRookMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
bool isKnightMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
bool isBishopMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
bool isQueenMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
bool isKingMove(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
bool canCastle(const int board[BOARD_SIZE][BOARD_SIZE],
               const Move &move,
               const BoardState &state);
