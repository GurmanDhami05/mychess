#include "piece_mapper.h"

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

int pieceToIndex(int piece)
{
    return piece + 6;
}
