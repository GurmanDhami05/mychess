#include "chess/promotion.h"
#include "chess/board.h"
#include <cstdlib>

bool promotePawn(Board &board, const Move &move)
{
    int piece = board.pieceAt(move.to);

    if (abs(piece) != 1)
    {
        return false;
    }

    int promotionRow = (piece > 0) ? 0 : BOARD_SIZE - 1;

    if (move.to.row == promotionRow)
    {
        int promotedPiece = (piece > 0) ? 5 : -5;
        board.setPiece(move.to, promotedPiece);
        return true;
    }
    return false;
}
