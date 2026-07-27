#include "chess/promotion.h"
#include "chess/board.h"
#include <cstdlib>

void promotePawn(Board &board, const Move &move)
{
    int piece = board.pieceAt(move.from);

    if (abs(piece) != 1)
    {
        return;
    }

    int promotionRow = (piece > 0) ? 0 : BOARD_SIZE - 1;

    if (move.to.row == promotionRow)
    {
        int promotedPiece = (piece > 0) ? 5 : -5;
        board.setPiece(move.to, promotedPiece);
    }
}
