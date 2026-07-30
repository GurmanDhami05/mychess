#pragma once
#include "chess/board.h"
#include "chess/position.h"
#include "chess/turn.h"

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

    [[nodiscard]] bool whiteCanCastleKingside() const
    {
        return !whiteKingMoved && !whiteKingsideRookMoved;
    }

    [[nodiscard]] bool whiteCanCastleQueenside() const
    {
        return !whiteKingMoved && !whiteQueensideRookMoved;
    }

    [[nodiscard]] bool blackCanCastleKingside() const
    {
        return !blackKingMoved && !blackKingsideRookMoved;
    }

    [[nodiscard]] bool blackCanCastleQueenside() const
    {
        return !blackKingMoved && !blackQueensideRookMoved;
    }

    void reset()
    {
        whiteKingMoved = true;
        whiteKingsideRookMoved = true;
        whiteQueensideRookMoved = true;

        blackKingMoved = true;
        blackKingsideRookMoved = true;
        blackQueensideRookMoved = true;
    }
};

struct GameState
{
    KingState whiteKing;
    KingState blackKing;

    bool checkmate = false;
    bool stalemate = false;

    CastlingRights castling;
    Position enPassantTarget = { -1, -1 };

    int halfMoveClock = 0;
    int fullMoveNumber = 1;

    int previousHalfMoveClock;
    int previousFullMoveNumber;
};

void updateGameState(GameState &state, Board &board, Turn currentTurn);
