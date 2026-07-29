#pragma once
#include <cstdint>

class ChessEngine;

uint64_t perft(ChessEngine &engine, int depth);
uint64_t perftDivide(ChessEngine &engine, int depth);
