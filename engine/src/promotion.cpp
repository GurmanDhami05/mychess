#include "chess/promotion.h"
#include <cstdlib>

void promotePawn(int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    int piece = board[move.to.row][move.to.col];

    if (abs(piece) != 1)
    {
        return;
    }

    int promotionRow = (piece > 0) ? 0 : BOARD_SIZE - 1;

    if (move.to.row == promotionRow)
    {
        board[move.to.row][move.to.col] = (piece > 0) ? 5 : -5;
    }
}
