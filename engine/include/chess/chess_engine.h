#pragma once

#include "chess/board.h"
#include "chess/game_state.h"
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

    Turn turn() const;

    GameState &state();
    Turn &turn();

    bool handleClick(int mouseX, int mouseY);

    void update();

    void updateCastlingRights(const Move &move, int movedPiece);

    void updateEnPassantTarget(const Move &move, int movedPiece);

    void switchTurn();
};
