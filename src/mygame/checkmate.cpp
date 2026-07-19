#include "mygame/checkmate.h"
#include "mygame/check.h"
#include "mygame/game.h"
#include "mygame/move.h"
#include "mygame/rules.h"

bool hasLegalMove(int board[BOARD_SIZE][BOARD_SIZE], Turn side)
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            int piece = board[row][col];
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

                        int capturedPiece = board[move.to.row][move.to.col];
                        movePiece(board, move);
                        bool legal = !isKingInCheck(board, side);
                        undoMove(board, move, capturedPiece);

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

bool isCheckmate(int board[BOARD_SIZE][BOARD_SIZE], Turn side)
{
    return (isKingInCheck(board, side) && !hasLegalMove(board, side));
}

bool isStalemate(int board[BOARD_SIZE][BOARD_SIZE], Turn side)
{
    return (!isKingInCheck(board, side) && !hasLegalMove(board, side));
}
