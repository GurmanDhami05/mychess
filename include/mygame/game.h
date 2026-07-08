#pragma once

#include "mygame/constants.h"
#include "mygame/move.h"

enum class Turn { White, Black };
bool isPlayerPiece(int piece, Turn currentTurn);
void switchTurn(Turn &currentTurn);
void movePiece(int board[BOARD_SIZE][BOARD_SIZE], const Move &move);
bool isEnemyPiece(int fromPiece, int toPiece);
