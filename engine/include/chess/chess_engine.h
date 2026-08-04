#pragma once

#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/move_info.h"
#include "chess/turn.h"
#include <string>
#include <vector>

class ChessEngine
{
  private:
    Board board_;
    mutable Board scratchBoard_;

    GameState state_;
    Turn turn_;

    std::vector<MoveInfo> moveHistory_;

  public:
    ChessEngine();

    const Board &board() const;

    const GameState &state() const;

    Turn turn() const;

    bool handleClick(Position clicked);

    void update();

    void updateCastlingRights(const Move &move, int movedPiece);

    void updateEnPassantTarget(const Move &move, int movedPiece);

    void switchTurn();

    bool tryMove(MoveInfo &info);
    void selectPiece(const Position pos);
    void finishMove(MoveInfo &info);

    int pieceAt(const Position &pos) const;

    void undoLastMove();

    bool makeMove(const Move &move);

    std::vector<Position> legalMoves(Position from) const;

    std::vector<Move> legalMoves() const;

    bool loadFEN(const std::string &fen);

    std::string exportFEN() const;
};
