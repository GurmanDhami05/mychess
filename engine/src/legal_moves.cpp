#include "chess/legal_moves.h"
#include "chess/check.h"
#include "chess/game.h"
#include "chess/game_state.h"
#include "chess/move.h"
#include "chess/rules.h"
#include <cstdlib>
#include <vector>

std::vector<Position>
getLegalMoves(Board &board, Position from, Turn side, const GameState &state)
{

    if (!isPlayerPiece(board.pieceAt(from), side))
    {
        return {};
    }

    std::vector<Position> legalMoves;
    int piece = board.pieceAt(from);
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

            int capturedPiece =
                enPassant ? board.pieceAt({ move.from.row, move.to.col })
                          : board.pieceAt(move.to);

            if (!isMoveLegal(board, move) && !castling && !enPassant)
            {
                continue;
            }

            if (castling)
            {
                board.performCastle(move);
            }
            else if (enPassant)
            {
                board.performEnPassant(move);
            }
            else
            {
                board.movePiece(move);
            }

            bool legal = !isKingInCheck(board, side);

            if (castling)
            {
                board.undoCastle(move);
            }
            else if (enPassant)
            {
                board.undoEnPassant(move, capturedPiece);
            }
            else
            {
                board.undoMove(move, capturedPiece);
            }

            if (legal)
            {
                legalMoves.push_back(to);
            }
        }
    }
    return legalMoves;
}
