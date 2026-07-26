#include "mygame/input.h"
#include "mygame/board_state.h"
#include "mygame/check.h"
#include "mygame/game.h"
#include "mygame/legal_moves.h"
#include "mygame/promotion.h"
#include "mygame/rules.h"

bool handleClick(int mouseX,
                 int mouseY,
                 int board[BOARD_SIZE][BOARD_SIZE],
                 Turn &currentTurn,
                 BoardState &state)
{

    if (state.checkmate || state.stalemate)
    {
        return false;
    }

    Position clicked{ mouseY / TILE_SIZE, mouseX / TILE_SIZE };

    int piece = board[clicked.row][clicked.col];

    if (!isPlayerPiece(piece, currentTurn) && state.selection.selected)
    {
        Move move{ state.selection.position, clicked };
        int movedPiece = board[move.from.row][move.from.col];

        bool castling = false;
        bool enPassant = false;
        int capturedPiece;

        if (abs(movedPiece) == 6)
        {
            castling = canCastle(board, move, state);
        }
        if (abs(movedPiece) == 1)
        {
            enPassant = canEnPassant(board, move, state);
        }

        if (enPassant)
        {
            capturedPiece = board[move.from.row][move.to.col];
        }
        else
        {
            capturedPiece = board[move.to.row][move.to.col];
        }

        if (!castling && !isMoveLegal(board, move) && !enPassant)
        {
            return false;
        }

        if (castling)
        {
            performCastle(board, move);
        }
        else if (enPassant)
        {
            performEnPassant(board, move);
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
            else if (enPassant)
            {
                undoEnPassant(board, move, capturedPiece);
            }
            else
            {
                undoMove(board, move, capturedPiece);
            }
            return false;
        }

        updateCastlingRights(move, movedPiece, state);
        updateEnPassantTarget(move, movedPiece, state);
        promotePawn(board, move);
        state.selection.selected = false;
        state.legalMoves.clear();
        state.selection.position = { -1, -1 };
        switchTurn(currentTurn);
        return true;
    }
    // if no piece is selected then first click
    else if (isPlayerPiece(piece, currentTurn))
    {
        state.selection.selected = true;
        state.selection.position = clicked;

        state.legalMoves = getLegalMoves(board, clicked, currentTurn, state);
    }

    return false;
}
