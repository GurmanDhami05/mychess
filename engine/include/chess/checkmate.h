#pragma once

#include "chess/game.h"

bool hasLegalMove(int board[BOARD_SIZE][BOARD_SIZE], Turn side);
bool isCheckmate(int board[BOARD_SIZE][BOARD_SIZE], Turn side);
bool isStalemate(int board[BOARD_SIZE][BOARD_SIZE], Turn side);
