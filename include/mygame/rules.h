#pragma once

#include "mygame/constants.h"
#include "mygame/move.h"

bool isMoveLegal(const int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
