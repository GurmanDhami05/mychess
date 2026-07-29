#pragma once

#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/move_info.h"
#include "chess/turn.h"

class ChessEngine
{
  private:
    Board board_;
    GameState state_;
    Turn turn_;

  public:
    ChessEngine();

    const Board &board() const;
    Board &board();

    const GameState &state() const;
    GameState &state();

    Turn turn() const;

    bool handleClick(Position clicked);

    void update();

    void updateCastlingRights(const Move &move, int movedPiece);

    void updateEnPassantTarget(const Move &move, int movedPiece);

    void switchTurn();

    bool tryMove(MoveInfo &info);
    void selectPiece(const Position pos);
    void finishMove(const MoveInfo &info);
};
