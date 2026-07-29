#pragma once
#include "chess/game_state.h"
#include "chess/position.h"
#include <vector>

std::vector<Position>
getLegalMoves(Board &board, Position from, Turn side, const GameState &state);

std::vector<Move>
getAllLegalMoves(Board &board, Turn side, const GameState &state);
