#include "chess/chess_engine.h"
#include "chess/board.h"
#include "chess/check.h"
#include "chess/game_state.h"
#include "chess/legal_moves.h"
#include "chess/piece.h"
#include "chess/promotion.h"
#include "chess/rules.h"
#include <stdlib.h>

ChessEngine::ChessEngine()
{
    turn_ = Turn::White;
    updateGameState(state_, board_, turn_);
}

const Board &ChessEngine::board() const
{
    return board_;
}

Board &ChessEngine::board()
{
    return board_;
}

const GameState &ChessEngine::state() const
{
    return state_;
}

GameState &ChessEngine::state()
{
    return state_;
}

Turn ChessEngine::turn() const
{
    return turn_;
}

Turn &ChessEngine::turn()
{
    return turn_;
}

void ChessEngine::update()
{
    updateGameState(state_, board_, turn_);
}

bool ChessEngine::handleClick(int mouseX, int mouseY)
{

    if (state_.checkmate || state_.stalemate)
    {
        return false;
    }

    Position clicked{ mouseY / TILE_SIZE, mouseX / TILE_SIZE };

    int piece = board_.pieceAt(clicked);

    if (!Piece::isPlayerPiece(piece, turn_) && state_.selection.selected)
    {
        Move move{ state_.selection.position, clicked };
        int movedPiece = board_.pieceAt(move.from);

        bool castling = false;
        bool enPassant = false;
        int capturedPiece;

        if (abs(movedPiece) == 6)
        {
            castling = canCastle(board_, move, state_);
        }
        if (abs(movedPiece) == 1)
        {
            enPassant = canEnPassant(board_, move, state_);
        }

        if (enPassant)
        {
            capturedPiece = board_.pieceAt({ move.from.row, move.to.col });
        }
        else
        {
            capturedPiece = board_.pieceAt(move.to);
        }

        if (!castling && !isMoveLegal(board_, move) && !enPassant)
        {
            return false;
        }

        if (castling)
        {
            board_.performCastle(move);
        }
        else if (enPassant)
        {
            board_.performEnPassant(move);
        }
        else
        {
            board_.movePiece(move);
        }

        if (isKingInCheck(board_, turn_))
        {
            if (castling)
            {
                board_.undoCastle(move);
            }
            else if (enPassant)
            {
                board_.undoEnPassant(move, capturedPiece);
            }
            else
            {
                board_.undoMove(move, capturedPiece);
            }
            return false;
        }

        updateCastlingRights(move, movedPiece);
        updateEnPassantTarget(move, movedPiece);
        promotePawn(board_, move);
        state_.selection.selected = false;
        state_.legalMoves.clear();
        state_.selection.position = { -1, -1 };
        switchTurn();
        return true;
    }
    // if no piece is selected then first click
    else if (Piece::isPlayerPiece(piece, turn_))
    {
        state_.selection.selected = true;
        state_.selection.position = clicked;

        state_.legalMoves = getLegalMoves(board_, clicked, turn_, state_);
    }

    return false;
}

void ChessEngine::updateCastlingRights(const Move &move, int movedPiece)
{
    if (movedPiece == 2 && move.from.row == 7 &&
        move.from.col == 0) // White queen-side rook
    {
        state_.castling.whiteQueensideRookMoved = true;
    }
    else if (movedPiece == 2 && move.from.row == 7 &&
             move.from.col == 7) // White king-side rook
    {
        state_.castling.whiteKingsideRookMoved = true;
    }
    else if (movedPiece == -2 && move.from.row == 0 &&
             move.from.col == 0) // Black queen-side rook
    {
        state_.castling.blackQueensideRookMoved = true;
    }
    else if (movedPiece == -2 && move.from.row == 0 &&
             move.from.col == 7) // Black king-side rook
    {
        state_.castling.blackKingsideRookMoved = true;
    }

    if (movedPiece == 6) // White king
    {
        state_.castling.whiteKingMoved = true;
    }
    else if (movedPiece == -6) // Black king
    {
        state_.castling.blackKingMoved = true;
    }
}

void ChessEngine::updateEnPassantTarget(const Move &move, int movedPiece)
{
    if (abs(movedPiece) == 1 && abs(move.to.row - move.from.row) == 2)
    {
        state_.enPassantTarget.row = (move.from.row + move.to.row) / 2;
        state_.enPassantTarget.col = move.from.col;
    }
    else
    {
        state_.enPassantTarget = { -1, -1 };
    }
}

void ChessEngine::switchTurn()
{
    if (turn_ == Turn::White)
    {
        turn_ = Turn::Black;
    }
    else
    {
        turn_ = Turn::White;
    }
}
