#pragma once

#include "board.h"
#include "turn.h"

bool hasLegalMove(Board &board, Turn side);
bool isCheckmate(Board &board, Turn side);
bool isStalemate(Board &board, Turn side);
