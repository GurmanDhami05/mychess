#pragma once
#include "mygame/constants.h"
#include "mygame/game.h"
#include "mygame/position.h"

Position getKingPosition(const int board[BOARD_SIZE][BOARD_SIZE],
                         Turn kingTurn);
bool attacksSquare(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);

bool isSquareAttacked(const int board[BOARD_SIZE][BOARD_SIZE],
                      const Position &square,
                      Turn attackerTurn);
bool isKingInCheck(const int board[BOARD_SIZE][BOARD_SIZE], Turn kingTurn);
