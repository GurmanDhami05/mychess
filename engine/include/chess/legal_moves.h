#pragma once
#include "chess/board_state.h"
#include "chess/constants.h"
#include "chess/position.h"
#include <vector>

std::vector<Position> getLegalMoves(int board[BOARD_SIZE][BOARD_SIZE],
                                    Position from,
                                    Turn side,
                                    const BoardState &state);
