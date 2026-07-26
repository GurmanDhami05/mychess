#pragma once

#include "chess/board_state.h"
#include "chess/constants.h"
#include "chess/game.h"
#include <SDL2/SDL.h>

bool handleClick(int mouseX,
                 int mouseY,
                 int board[BOARD_SIZE][BOARD_SIZE],
                 Turn &currentTurn,
                 BoardState &state);
