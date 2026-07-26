#pragma once

#include "chess/board_state.h"
#include "chess/constants.h"
#include "chess/move.h"

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
bool canEnPassant(const int board[BOARD_SIZE][BOARD_SIZE],
                  const Move &move,
                  const BoardState &state);
