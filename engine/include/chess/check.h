#pragma once
#include "chess/board.h"
#include "chess/position.h"
#include "chess/turn.h"

Position getKingPosition(const Board &board, Turn kingTurn);
bool attacksSquare(const Board &board, const Move &move);

bool isSquareAttacked(const Board &board,
                      const Position &square,
                      Turn attackerTurn);
bool isKingInCheck(const Board &board, Turn kingTurn);
