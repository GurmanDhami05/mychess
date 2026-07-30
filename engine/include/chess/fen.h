#pragma once
#include "chess/board.h"
#include "chess/game_state.h"
#include <string>

char pieceToFenChar(int piece);
int fenCharToPiece(char c);

namespace FEN
{
std::string
exportFEN(const Board &board, Turn turn, const GameState &gameState);
bool loadFEN(Board &board,
             Turn &turn,
             GameState &gameState,
             const std::string &fen);
} // namespace FEN
