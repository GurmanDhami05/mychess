#pragma once

#include "chess/turn.h"

namespace Piece
{
bool isPlayerPiece(int piece, Turn turn);

bool isEnemyPiece(int fromPiece, int toPiece);

constexpr int None = 0;
constexpr int WhitePawn = 1;
constexpr int WhiteRook = 2;
constexpr int WhiteKnight = 3;
constexpr int WhiteBishop = 4;
constexpr int WhiteQueen = 5;
constexpr int WhiteKing = 6;
constexpr int BlackPawn = -1;
constexpr int BlackRook = -2;
constexpr int BlackKnight = -3;
constexpr int BlackBishop = -4;
constexpr int BlackQueen = -5;
constexpr int BlackKing = -6;

} // namespace Piece
