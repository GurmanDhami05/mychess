#include "chess/checkmate.h"
#include "chess/check.h"
#include "chess/game.h"
#include "chess/move.h"
#include "chess/rules.h"

bool hasLegalMove(Board &board, Turn side)
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            int piece = board.pieceAt({ row, col });
            if (isPlayerPiece(piece, side))
            {
                for (int toRow = 0; toRow < BOARD_SIZE; ++toRow)
                {
                    for (int toCol = 0; toCol < BOARD_SIZE; ++toCol)
                    {
                        Move move{ { row, col }, { toRow, toCol } };
                        if (!isMoveLegal(board, move))
                        {
                            continue;
                        }

                        int capturedPiece = board.pieceAt(move.to);
                        board.movePiece(move);
                        bool legal = !isKingInCheck(board, side);
                        board.undoMove(move, capturedPiece);

                        if (legal)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool isCheckmate(Board &board, Turn side)
{
    return (isKingInCheck(board, side) && !hasLegalMove(board, side));
}

bool isStalemate(Board &board, Turn side)
{
    return (!isKingInCheck(board, side) && !hasLegalMove(board, side));
}
