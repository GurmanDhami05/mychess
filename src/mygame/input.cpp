#include "mygame/input.h"
#include "mygame/board_state.h"
#include "mygame/check.h"
#include "mygame/game.h"
#include "mygame/rules.h"

bool handleClick(int mouseX,
                 int mouseY,
                 int board[BOARD_SIZE][BOARD_SIZE],
                 Turn &currentTurn,
                 BoardState &state)
{

    Position clicked{ mouseY / TILE_SIZE, mouseX / TILE_SIZE };

    int piece = board[clicked.row][clicked.col];

    // if the second clicked piece is not playerpiece and there is a piece
    // already slected
    if (!isPlayerPiece(piece, currentTurn) && state.selection.selected)
    {
        Move move{ state.selection.position, clicked };
        if (!(isMoveLegal(board, move)))
        {
            return false;
        }

        int capturedPiece = board[move.to.row][move.to.col];
        movePiece(board, move);

        if (isKingInCheck(board, currentTurn))
        {
            undoMove(board, move, capturedPiece);
            return false;
        }

        state.selection.selected = false;
        switchTurn(currentTurn);
        return true;
    }
    // if no piece is selected then first click
    else if (isPlayerPiece(piece, currentTurn))
    {
        state.selection.selected = true;
        state.selection.position = clicked;
    }

    if (state.checkmate || state.stalemate)
    {
        return false;
    }

    return false;
}
