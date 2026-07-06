#include "mygame/input.h"
#include "mygame/game.h"
#include "mygame/rules.h"

void handleLeftClick(int mouseX,
                     int mouseY,
                     int board[BOARD_SIZE][BOARD_SIZE],
                     PieceSelected &selection,
                     Turn &currentTurn) {

    int col = mouseX / TILE_SIZE;
    int row = mouseY / TILE_SIZE;

    int piece = board[row][col];

    if (!isPlayerPiece(piece, currentTurn) && selection.selected) {
        Move move{ selection.row, selection.col, row, col };
        if (isMoveLegal(board, move)) {
            movePiece(board, move);
            selection.selected = false;
            switchTurn(currentTurn);
        }
    } else if (isPlayerPiece(piece, currentTurn)) {
        selection.selected = true;
        selection.row = row;
        selection.col = col;
    }
}
