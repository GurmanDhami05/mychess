#include "chess/chess_engine.h"
#include "chess/board.h"
#include "chess/check.h"
#include "chess/game.h"
#include "chess/game_state.h"
#include "chess/legal_moves.h"
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

    if (!isPlayerPiece(piece, turn_) && state_.selection.selected)
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

        updateCastlingRights(move, movedPiece, state_);
        updateEnPassantTarget(move, movedPiece, state_);
        promotePawn(board_, move);
        state_.selection.selected = false;
        state_.legalMoves.clear();
        state_.selection.position = { -1, -1 };
        switchTurn(turn_);
        return true;
    }
    // if no piece is selected then first click
    else if (isPlayerPiece(piece, turn_))
    {
        state_.selection.selected = true;
        state_.selection.position = clicked;

        state_.legalMoves = getLegalMoves(board_, clicked, turn_, state_);
    }

    return false;
}
