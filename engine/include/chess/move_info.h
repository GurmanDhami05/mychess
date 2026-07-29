#pragma once

#include "chess/game_state.h"
#include "chess/move.h"

struct MoveInfo
{

    explicit MoveInfo(const Move &move) : move(move)
    {
    }

    Move move;

    int movedPiece = 0;
    int capturedPiece = 0;

    bool castling = false;
    bool enPassant = false;

    CastlingRights previousCastlingRights;
    Position previousEnPassantTarget;

    bool promotion = false;
};
