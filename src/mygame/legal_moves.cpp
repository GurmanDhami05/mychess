#include "mygame/legal_moves.h"
#include "mygame/board_state.h"
#include "mygame/check.h"
#include "mygame/game.h"
#include "mygame/move.h"
#include "mygame/rules.h"
#include <cstdlib>
#include <vector>

std::vector<Position> getLegalMoves(int board[BOARD_SIZE][BOARD_SIZE],
                                    Position from,
                                    Turn side,
                                    const BoardState &state)
{

    if (!isPlayerPiece(board[from.row][from.col], side))
    {
        return {};
    }

    std::vector<Position> legalMoves;
    int piece = board[from.row][from.col];
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {

            bool castling = false;
            bool enPassant = false;
            Position to{ row, col };
            Move move{ from, to };

            if (abs(piece) == 6) // King
            {
                castling = canCastle(board, move, state);
            }
            else if (abs(piece) == 1) // Pawn
            {
                enPassant = canEnPassant(board, move, state);
            }

            int capturedPiece = enPassant ? board[move.from.row][move.to.col]
                                          : board[move.to.row][move.to.col];

            if (!isMoveLegal(board, move) && !castling && !enPassant)
            {
                continue;
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

            bool legal = !isKingInCheck(board, side);

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

            if (legal)
            {
                legalMoves.push_back(to);
            }
        }
    }
    return legalMoves;
}
