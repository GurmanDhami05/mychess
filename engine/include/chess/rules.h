#pragma once

#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/move.h"

bool isMoveLegal(const Board &board, const Move &move);

bool isPawnMove(const Board &board, const Move &move);
bool isRookMove(const Board &board, const Move &move);
bool isKnightMove(const Board &board, const Move &move);
bool isBishopMove(const Board &board, const Move &move);
bool isQueenMove(const Board &board, const Move &move);
bool isKingMove(const Board &board, const Move &move);
bool canCastle(const Board &board, const Move &move, const GameState &state);
bool canEnPassant(const Board &board, const Move &move, const GameState &state);
