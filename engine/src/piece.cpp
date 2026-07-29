#include "chess/piece.h"
#include "chess/constants.h"
#include "chess/turn.h"

bool Piece::isPlayerPiece(int piece, Turn turn)
{
    if (piece == EMPTY)
    {
        return false;
    }
    if (turn == Turn::White)
    {
        return piece > 0;
    }
    return piece < 0;
}

bool Piece::isEnemyPiece(int fromPiece, int toPiece)
{
    return ((fromPiece > 0 && toPiece < 0) || (fromPiece < 0 && toPiece > 0));
}
