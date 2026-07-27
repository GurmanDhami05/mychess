#pragma once
#include "chess/board.h"
#include "chess/piece_selected.h"
#include "chess/position.h"
#include "chess/turn.h"
#include <vector>

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

struct GameState
{
    PieceSelected selection;

    KingState whiteKing;
    KingState blackKing;

    bool checkmate = false;
    bool stalemate = false;

    CastlingRights castling;

    Position enPassantTarget = { -1, -1 };

    std::vector<Position> legalMoves;
};

void updateGameState(GameState &state, Board &board, Turn currentTurn);
