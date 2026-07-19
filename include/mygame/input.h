#pragma once

#include "mygame/board_state.h"
#include "mygame/constants.h"
#include "mygame/game.h"
#include <SDL2/SDL.h>

bool handleClick(int mouseX,
                 int mouseY,
                 int board[BOARD_SIZE][BOARD_SIZE],
                 Turn &currentTurn,
                 BoardState &state);
