#include "mygame/board.h"

#include <array>
#include <iostream>

const std::array<std::string, 13> piecesLUT = {
    "black_king",   // index 0
    "black_queen",  // index 1
    "black_bishop", // index 2
    "black_knight", // index 3
    "black_rook",   // index 4
    "black_pawn",   // index 5
    "",             // index 6 (empty)
    "white_pawn",   // index 7
    "white_rook",   // index 8
    "white_knight", // index 9
    "white_bishop", // index 10
    "white_queen",  // index 11
    "white_king"    // index 12
};

int pieceToIndex(int piece) { return piece + 6; }

void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (row == 1) {
                board[row][col] = -1;
            } else if (row == 6) {
                board[row][col] = 1;
            } else {
                board[row][col] = EMPTY;
            }
        }
    }

    // black pieces
    board[0][0] = -2; // b_rook
    board[0][1] = -3; // b_knight
    board[0][2] = -4; // b_bishop
    board[0][3] = -5; // b_queen
    board[0][4] = -6; // b_king
    board[0][5] = -4; // b_bishop
    board[0][6] = -3; // b_knight
    board[0][7] = -2; // b_rook

    // white pieces
    board[7][0] = 2; // w_rook
    board[7][1] = 3; // w_knight
    board[7][2] = 4; // w_bishop
    board[7][3] = 5; // w_queen
    board[7][4] = 6; // w_king
    board[7][5] = 4; // w_bishop
    board[7][6] = 3; // w_knight
    board[7][7] = 2; // w_rook
}

void printBoard(const int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            std::cout << board[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}
