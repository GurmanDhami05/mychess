#pragma once

#include "chess/constants.h"
#include "chess/move.h"

class Board
{
  private:
    int squares_[BOARD_SIZE][BOARD_SIZE];
    void initialize();

  public:
    Board();

    int pieceAt(const Position &pos) const;

    void setPiece(const Position &pos, int piece);

    bool isEmpty(const Position &pos) const;

    bool isInside(const Position &pos) const;

    void movePiece(const Move &move);
    void undoMove(const Move &move, int capturedPiece);

    void performCastle(const Move &kingMove);
    void undoCastle(const Move &kingMove);

    void performEnPassant(const Move &move);
    void undoEnPassant(const Move &move, int capturedPawnRow);

    void printBoard() const;
};
