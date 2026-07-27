#pragma once

#include "chess/game_state.h"
#include "chess/move.h"

bool isPlayerPiece(int piece, Turn currentTurn);
void switchTurn(Turn &currentTurn);
bool isEnemyPiece(int fromPiece, int toPiece);
void updateCastlingRights(const Move &move, int movedPiece, GameState &state);
void updateEnPassantTarget(const Move &move, int movedPiece, GameState &state);
