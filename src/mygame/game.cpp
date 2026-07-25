#include "mygame/game.h"
#include "mygame/board_state.h"
#include "mygame/move.h"
#include <cstdlib>

bool isPlayerPiece(int piece, Turn currentTurn)
{
    if (piece == EMPTY)
    {
        return false;
    }
    if (currentTurn == Turn::White)
    {
        return piece > 0;
    }
    return piece < 0;
}

bool isEnemyPiece(int fromPiece, int toPiece)
{
    return ((fromPiece > 0 && toPiece < 0) || (fromPiece < 0 && toPiece > 0));
}

void switchTurn(Turn &currentTurn)
{
    if (currentTurn == Turn::White)
    {
        currentTurn = Turn::Black;
    }
    else
    {
        currentTurn = Turn::White;
    }
}

void movePiece(int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    board[move.to.row][move.to.col] = board[move.from.row][move.from.col];
    board[move.from.row][move.from.col] = EMPTY;
}

void undoMove(int board[BOARD_SIZE][BOARD_SIZE],
              const Move &move,
              int capturedPiece)
{
    board[move.from.row][move.from.col] = board[move.to.row][move.to.col];
    board[move.to.row][move.to.col] = capturedPiece;
}

void updateCastlingRights(const Move &move, int movedPiece, BoardState &state)
{
    if (movedPiece == 2 && move.from.row == 7 &&
        move.from.col == 0) // White queen-side rook
    {
        state.castling.whiteQueensideRookMoved = true;
    }
    else if (movedPiece == 2 && move.from.row == 7 &&
             move.from.col == 7) // White king-side rook
    {
        state.castling.whiteKingsideRookMoved = true;
    }
    else if (movedPiece == -2 && move.from.row == 0 &&
             move.from.col == 0) // Black queen-side rook
    {
        state.castling.blackQueensideRookMoved = true;
    }
    else if (movedPiece == -2 && move.from.row == 0 &&
             move.from.col == 7) // Black king-side rook
    {
        state.castling.blackKingsideRookMoved = true;
    }

    if (movedPiece == 6) // White king
    {
        state.castling.whiteKingMoved = true;
    }
    else if (movedPiece == -6) // Black king
    {
        state.castling.blackKingMoved = true;
    }
}

void performCastle(int board[BOARD_SIZE][BOARD_SIZE], const Move &kingMove)
{
    int row = kingMove.from.row;
    movePiece(board, kingMove); // Move the king first

    if (kingMove.to.col == 6) // King-side castle
    {
        Move rookMove{ { row, 7 }, { row, 5 } };
        movePiece(board, rookMove);
    }
    else if (kingMove.to.col == 2) // Queen-side castle
    {
        Move rookMove{ { row, 0 }, { row, 3 } };
        movePiece(board, rookMove);
    }
}

void undoCastle(int board[BOARD_SIZE][BOARD_SIZE], const Move &kingMove)
{
    int row = kingMove.from.row;
    undoMove(board, kingMove, EMPTY); // Undo the king's move

    if (kingMove.to.col == 6) // King-side castle
    {
        Move rookMove{ { row, 5 }, { row, 7 } };
        undoMove(board, rookMove, EMPTY);
    }
    else if (kingMove.to.col == 2) // Queen-side castle
    {
        Move rookMove{ { row, 3 }, { row, 0 } };
        undoMove(board, rookMove, EMPTY);
    }
}

void updateEnPassantTarget(const Move &move, int movedPiece, BoardState &state)
{
    if (abs(movedPiece) == 1 && abs(move.to.row - move.from.row) == 2)
    {
        state.enPassantTarget.row = (move.from.row + move.to.row) / 2;
        state.enPassantTarget.col = move.from.col;
    }
    else
    {
        state.enPassantTarget = { -1, -1 };
    }
}

void performEnPassant(int board[BOARD_SIZE][BOARD_SIZE], const Move &move)
{
    int capturedPawnRow = move.from.row;
    int capturedPawnCol = move.to.col;

    // Move the pawn
    movePiece(board, move);

    // Remove the captured pawn
    board[capturedPawnRow][capturedPawnCol] = EMPTY;
}

void undoEnPassant(int board[BOARD_SIZE][BOARD_SIZE],
                   const Move &move,
                   int capturedPawn)
{
    int capturedPawnRow = move.from.row;
    int capturedPawnCol = move.to.col;

    // Undo the pawn's move
    undoMove(board, move, EMPTY);

    // Restore the captured pawn
    board[capturedPawnRow][capturedPawnCol] = capturedPawn;
}
