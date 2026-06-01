# Chess Project Notes

## Current Architecture

Functions:

- initWindow()
- initRenderer()
- drawBoard()
- render()

## Board Representation

int board[8][8]

Positive = white
Negative = black
0 = empty

Pieces:
1 = pawn
2 = rook
3 = knight
4 = bishop
5 = queen
6 = king

## Current Goal

Render piece PNG textures using board array data.

Board state should remain the single source of truth.

## Future Goals

- Mouse input
- Piece selection
- Piece movement
- Move validation
- Check/checkmate
