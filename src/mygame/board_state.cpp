#include "mygame/board_state.h"
#include "mygame/check.h"
#include "mygame/constants.h"

void updateBoardState(BoardState &state,
                      const int board[BOARD_SIZE][BOARD_SIZE])
{
    state.whiteKing.position = getKingPosition(board, Turn::White);
    state.blackKing.position = getKingPosition(board, Turn::Black);

    state.whiteKing.inCheck = isKingInCheck(board, Turn::White);
    state.blackKing.inCheck = isKingInCheck(board, Turn::Black);
}
