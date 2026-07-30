#include "chess/chess_engine.h"
#include "chess/board.h"
#include "chess/check.h"
#include "chess/game_state.h"
#include "chess/move_info.h"
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

bool ChessEngine::tryMove(MoveInfo &info)
{

    info.movedPiece = board_.pieceAt(info.move.from);

    info.previousCastlingRights = state_.castling;
    info.previousEnPassantTarget = state_.enPassantTarget;

    if (abs(info.movedPiece) == 6)
    {
        info.castling = canCastle(board_, info.move, state_);
    }
    if (abs(info.movedPiece) == 1)
    {
        info.enPassant = canEnPassant(board_, info.move, state_);
    }

    if (info.enPassant)
    {
        info.capturedPiece =
            board_.pieceAt({ info.move.from.row, info.move.to.col });
    }
    else
    {
        info.capturedPiece = board_.pieceAt(info.move.to);
    }

    if (!info.castling && !isMoveLegal(board_, info.move) && !info.enPassant)
    {
        return false;
    }

    if (info.castling)
    {
        board_.performCastle(info.move);
    }
    else if (info.enPassant)
    {
        board_.performEnPassant(info.move);
    }
    else
    {
        board_.movePiece(info.move);
    }

    if (isKingInCheck(board_, turn_))
    {
        if (info.castling)
        {
            board_.undoCastle(info.move);
        }
        else if (info.enPassant)
        {
            board_.undoEnPassant(info.move, info.capturedPiece);
        }
        else
        {
            board_.undoMove(info.move, info.capturedPiece);
        }
        return false;
    }
    return true;
}

void ChessEngine::finishMove(MoveInfo &info)
{
    info.previousHalfMoveClock = state_.halfMoveClock;
    info.previousFullMoveNumber = state_.fullMoveNumber;
    if (info.capturedPiece != Piece::None ||
        std::abs(info.movedPiece) == Piece::WhitePawn)
    {
        state_.halfMoveClock = 0;
    }
    else
    {
        ++state_.halfMoveClock;
    }

    if (turn_ == Turn::Black)
    {
        ++state_.fullMoveNumber;
    }
    updateCastlingRights(info.move, info.movedPiece);
    updateEnPassantTarget(info.move, info.movedPiece);
    info.promotion = promotePawn(board_, info.move);
    switchTurn();
}

void ChessEngine::undoLastMove()
{
    if (moveHistory_.empty())
    {
        return;
    }

    MoveInfo lastMove = moveHistory_.back();
    moveHistory_.pop_back();

    if (lastMove.castling)
    {
        board_.undoCastle(lastMove.move);
    }
    else if (lastMove.enPassant)
    {
        board_.undoEnPassant(lastMove.move, lastMove.capturedPiece);
    }
    else
    {
        board_.undoMove(lastMove.move, lastMove.capturedPiece);
    }
    if (lastMove.promotion)
    {
        board_.setPiece(lastMove.move.from, lastMove.movedPiece);
    }

    state_.castling = lastMove.previousCastlingRights;
    state_.enPassantTarget = lastMove.previousEnPassantTarget;
    state_.halfMoveClock = lastMove.previousHalfMoveClock;
    state_.fullMoveNumber = lastMove.previousFullMoveNumber;

    switchTurn();

    update();
}

bool ChessEngine::makeMove(const Move &move)
{
    MoveInfo info{ move };
    if (tryMove(info))
    {
        finishMove(info);
        moveHistory_.push_back(info);
        return true;
    }
    return false;
}
