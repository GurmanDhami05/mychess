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

    if (!isPlayerPiece(piece, currentTurn) && state.selection.selected)
    {
        Move move{ state.selection.position, clicked };
        int movedPiece = board[move.from.row][move.from.col];

        bool castling = false;

        if (abs(movedPiece) == 6)
        {
            castling = canCastle(board, move, state);
        }

        if (!castling && !isMoveLegal(board, move))
        {
            return false;
        }

        int capturedPiece = board[move.to.row][move.to.col];

        if (castling)
        {
            performCastle(board, move);
        }
        else
        {
            movePiece(board, move);
        }

        if (isKingInCheck(board, currentTurn))
        {
            if (castling)
            {
                undoCastle(board, move);
            }
            else
            {
                undoMove(board, move, capturedPiece);
            }
            return false;
        }

        updateCastlingRights(move, movedPiece, state);
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
