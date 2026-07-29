#include "chess/board.h"

#include <iostream>

Board::Board()
{
    initialize();
}

void Board::initialize()
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (row == 1)
            {
                squares_[row][col] = -1;
            }
            else if (row == 6)
            {
                squares_[row][col] = 1;
            }
            else
            {
                squares_[row][col] = EMPTY;
            }
        }
    }

    // black pieces
    squares_[0][0] = -2; // b_rook
    squares_[0][1] = -3; // b_knight
    squares_[0][2] = -4; // b_bishop
    squares_[0][3] = -5; // b_queen
    squares_[0][4] = -6; // b_king
    squares_[0][5] = -4; // b_bishop
    squares_[0][6] = -3; // b_knight
    squares_[0][7] = -2; // b_rook

    // white pieces
    squares_[7][0] = 2; // w_rook
    squares_[7][1] = 3; // w_knight
    squares_[7][2] = 4; // w_bishop
    squares_[7][3] = 5; // w_queen
    squares_[7][4] = 6; // w_king
    squares_[7][5] = 4; // w_bishop
    squares_[7][6] = 3; // w_knightboard
    squares_[7][7] = 2; // w_rook
}

int Board::pieceAt(const Position &pos) const
{
    return squares_[pos.row][pos.col];
}

void Board::setPiece(const Position &pos, int piece)
{
    squares_[pos.row][pos.col] = piece;
}

bool Board::isEmpty(const Position &pos) const
{
    return squares_[pos.row][pos.col] == EMPTY;
}

bool Board::isInside(const Position &pos) const
{
    return pos.row >= 0 && pos.row < BOARD_SIZE && pos.col >= 0 &&
           pos.col < BOARD_SIZE;
}

void Board::movePiece(const Move &move)
{

    squares_[move.to.row][move.to.col] = squares_[move.from.row][move.from.col];
    squares_[move.from.row][move.from.col] = EMPTY;
}

void Board::undoMove(const Move &move, int capturedPiece)
{
    squares_[move.from.row][move.from.col] = squares_[move.to.row][move.to.col];
    squares_[move.to.row][move.to.col] = capturedPiece;
}

void Board::performCastle(const Move &kingMove)
{
    int row = kingMove.from.row;
    movePiece(kingMove); // Move the king first

    if (kingMove.to.col == 6) // King-side castle
    {
        Move rookMove{ { row, 7 }, { row, 5 } };
        movePiece(rookMove);
    }
    else if (kingMove.to.col == 2) // Queen-side castle
    {
        Move rookMove{ { row, 0 }, { row, 3 } };
        movePiece(rookMove);
    }
}

void Board::undoCastle(const Move &kingMove)
{
    int row = kingMove.from.row;
    undoMove(kingMove, EMPTY);

    if (kingMove.to.col == 6)
    {
        Move rookMove{ { row, 7 }, { row, 5 } };
        undoMove(rookMove, EMPTY);
    }
    else if (kingMove.to.col == 2)
    {
        Move rookMove{ { row, 0 }, { row, 3 } };
        undoMove(rookMove, EMPTY);
    }
}

void Board::performEnPassant(const Move &move)
{
    int capturedPawnRow = move.from.row;
    int capturedPawnCol = move.to.col;

    // Move the pawn
    movePiece(move);

    // Remove the captured pawn
    squares_[capturedPawnRow][capturedPawnCol] = EMPTY;
}

void Board::undoEnPassant(const Move &move, int capturedPawn)
{
    int capturedPawnRow = move.from.row;
    int capturedPawnCol = move.to.col;

    // Undo the pawn's move
    undoMove(move, EMPTY);

    // Restore the captured pawn
    squares_[capturedPawnRow][capturedPawnCol] = capturedPawn;
}

void Board::printBoard() const
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            std::cout << squares_[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}
