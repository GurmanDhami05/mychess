#pragma once

#include "chess/position.h"

struct Move
{
    Position from;
    Position to;

    int previousHalfMoveClock;
    int previousFullMoveNumber;
};
