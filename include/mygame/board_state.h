
#pragma once
#include "mygame/constants.h"
#include "mygame/piece_selected.h"
#include "mygame/position.h"
#include "mygame/turn.h"

struct KingState
{
    Position position;
    bool inCheck;
};

struct CastlingRights
{
    bool whiteKingMoved = false;

    bool whiteKingsideRookMoved = false;
    bool whiteQueensideRookMoved = false;

    bool blackKingMoved = false;

    bool blackKingsideRookMoved = false;
    bool blackQueensideRookMoved = false;
};

struct BoardState
{
    PieceSelected selection;

    KingState whiteKing;
    KingState blackKing;

    bool checkmate = false;
    bool stalemate = false;

    CastlingRights castling;

    Position enPassantTarget = { -1, -1 };
};

void updateBoardState(BoardState &state,
                      int board[BOARD_SIZE][BOARD_SIZE],
                      Turn currentTurn);
