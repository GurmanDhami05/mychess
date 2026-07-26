#pragma once
#include "mygame/board_state.h"
#include "mygame/constants.h"
#include "mygame/position.h"
#include <vector>

std::vector<Position> getLegalMoves(int board[BOARD_SIZE][BOARD_SIZE],
                                    Position from,
                                    Turn side,
                                    const BoardState &state);
