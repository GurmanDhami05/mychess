#pragma once

#include "chess/turn.h"

namespace Piece
{
bool isPlayerPiece(int piece, Turn turn);

bool isEnemyPiece(int fromPiece, int toPiece);
} // namespace Piece
