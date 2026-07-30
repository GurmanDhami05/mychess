#pragma once

#include "chess/constants.h"

struct Position
{
    int row;
    int col;

    [[nodiscard]] bool isValid() const
    {
        return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
    }
};
