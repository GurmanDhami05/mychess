#include "chess/game_state.h"
#include "chess/check.h"
#include "chess/checkmate.h"

void updateGameState(GameState &state, Board &board, Turn currentTurn)
{
    state.whiteKing.position = getKingPosition(board, Turn::White);
    state.blackKing.position = getKingPosition(board, Turn::Black);

    state.whiteKing.inCheck = isKingInCheck(board, Turn::White);
    state.blackKing.inCheck = isKingInCheck(board, Turn::Black);

    state.checkmate = isCheckmate(board, currentTurn);
    state.stalemate = isStalemate(board, currentTurn);
}
