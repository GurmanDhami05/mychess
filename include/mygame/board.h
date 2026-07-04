#pragma once

#include "mygame/constants.h"
#include <array>
#include <string>

extern const std::array<std::string, 13> piecesLUT;

void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]);
void printBoard(const int board[BOARD_SIZE][BOARD_SIZE]);
int pieceToIndex(int piece);
