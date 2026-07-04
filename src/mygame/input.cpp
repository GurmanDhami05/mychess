#include "mygame/input.h"
#include "mygame/board.h"

#include <string>

void handleLeftClick(int mouseX,
                     int mouseY,
                     int board[BOARD_SIZE][BOARD_SIZE],
                     SDL_Event event,
                     PieceSelected &selection) {

    int col = mouseX / TILE_SIZE;
    int row = mouseY / TILE_SIZE;

    int piece = board[row][col];
    std::string pieceClicked = piecesLUT[pieceToIndex(piece)];

    if (piece == EMPTY) {
        if (selection.selected) {
            board[row][col] = board[selection.row][selection.col];
            board[selection.row][selection.col] = EMPTY;
            selection.selected = false;
        } else {
            selection.selected = false;
        }
    } else {
        // std::cout << "pieceClicked: " << pieceClicked << std::endl;
        selection.selected = true;
        selection.row = row;
        selection.col = col;
    }
}
