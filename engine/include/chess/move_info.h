#pragma once

#include "chess/move.h"

struct MoveInfo
{

    explicit MoveInfo(const Move &move) : move(move)
    {
    }

    Move move;

    int movedPiece;
    int capturedPiece;

    bool castling = false;
    bool enPassant = false;
};
