
#pragma once
#include "mygame/constants.h"
#include "mygame/piece_selected.h"
#include "mygame/position.h"

struct KingState
{
    Position position;
    bool inCheck;
};

struct BoardState
{
    PieceSelected selection;

    KingState whiteKing;
    KingState blackKing;
};

void updateBoardState(BoardState &state,
                      const int board[BOARD_SIZE][BOARD_SIZE]);
