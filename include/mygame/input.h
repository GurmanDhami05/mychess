#pragma once

#include "mygame/constants.h"
#include "mygame/game.h"
#include <SDL2/SDL.h>

struct PieceSelected {
    bool selected = false;
    int row;
    int col;
};

void handleLeftClick(int mouseX,
                     int mouseY,
                     int board[BOARD_SIZE][BOARD_SIZE],
                     PieceSelected &selection,
                     Turn &currentTurn);
