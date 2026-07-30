#pragma once

#include "chess/piece_selected.h"
#include <vector>

struct UIState
{
    PieceSelected selection;
    std::vector<Position> legalMoves;
};
