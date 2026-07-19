
#pragma once
#include "mygame/constants.h"
#include "mygame/game.h"
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

    bool checkmate = false;
    bool stalemate = false;
};

void updateBoardState(BoardState &state,
                      int board[BOARD_SIZE][BOARD_SIZE],
                      Turn currentTurn);
