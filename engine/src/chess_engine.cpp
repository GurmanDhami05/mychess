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

void ChessEngine::update()
{
    updateGameState(state_, board_, turn_);
}

bool ChessEngine::handleClick(Position clicked)
{

    if (state_.checkmate || state_.stalemate)
    {
        return false;
    }

    int piece = board_.pieceAt(clicked);

    if (!Piece::isPlayerPiece(piece, turn_) && state_.selection.selected)
    {
        Move move{ state_.selection.position, clicked };
        int movedPiece = board_.pieceAt(move.from);

        if (tryMove(move))
        {
            finishMove(move, movedPiece);
            return true;
        }
        return false;
    }
    // if no piece is selected then first click
    else if (Piece::isPlayerPiece(piece, turn_))
    {
        selectPiece(clicked);
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
    turn_ = (turn_ == Turn::White) ? Turn::Black : Turn::White;
}

bool ChessEngine::tryMove(const Move &move)
{

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
    return true;
}

void ChessEngine::selectPiece(const Position pos)
{
    state_.selection.selected = true;
    state_.selection.position = pos;

    state_.legalMoves = getLegalMoves(board_, pos, turn_, state_);
}

void ChessEngine::finishMove(const Move &move, const int movedPiece)
{
    updateCastlingRights(move, movedPiece);
    updateEnPassantTarget(move, movedPiece);
    promotePawn(board_, move);
    state_.selection.selected = false;
    state_.legalMoves.clear();
    state_.selection.position = { -1, -1 };
    switchTurn();
}
