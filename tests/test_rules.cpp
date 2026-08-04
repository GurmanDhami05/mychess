#include <gtest/gtest.h>

#include <chess/board.h>
#include <chess/game_state.h>
#include <chess/piece.h>
#include <chess/rules.h>

class RulesTest : public ::testing::Test
{
  protected:
    Board board;
    GameState state;

    void SetUp() override
    {
        board.clear();
    }
};

// ----------------------------------------------------
// Pawn
// ----------------------------------------------------

TEST_F(RulesTest, PawnMovesOneSquareForward)
{
    board.setPiece({ 6, 4 }, Piece::WhitePawn);

    EXPECT_TRUE(isPawnMove(board, { { 6, 4 }, { 5, 4 } }));
}

TEST_F(RulesTest, PawnMovesTwoSquaresInitially)
{
    board.setPiece({ 6, 4 }, Piece::WhitePawn);

    EXPECT_TRUE(isPawnMove(board, { { 6, 4 }, { 4, 4 } }));
}

TEST_F(RulesTest, PawnCannotJumpPiece)
{
    board.setPiece({ 6, 4 }, Piece::WhitePawn);
    board.setPiece({ 5, 4 }, Piece::BlackKnight);

    EXPECT_FALSE(isPawnMove(board, { { 6, 4 }, { 4, 4 } }));
}

TEST_F(RulesTest, PawnCapturesDiagonally)
{
    board.setPiece({ 6, 4 }, Piece::WhitePawn);
    board.setPiece({ 5, 5 }, Piece::BlackKnight);

    EXPECT_TRUE(isPawnMove(board, { { 6, 4 }, { 5, 5 } }));
}

TEST_F(RulesTest, PawnCannotCaptureForward)
{
    board.setPiece({ 6, 4 }, Piece::WhitePawn);
    board.setPiece({ 5, 4 }, Piece::BlackKnight);

    EXPECT_FALSE(isPawnMove(board, { { 6, 4 }, { 5, 4 } }));
}

// ----------------------------------------------------
// Rook
// ----------------------------------------------------

TEST_F(RulesTest, RookMovesHorizontally)
{
    board.setPiece({ 4, 4 }, Piece::WhiteRook);

    EXPECT_TRUE(isRookMove(board, { { 4, 4 }, { 4, 0 } }));
}

TEST_F(RulesTest, RookBlockedByPiece)
{
    board.setPiece({ 4, 4 }, Piece::WhiteRook);
    board.setPiece({ 4, 2 }, Piece::WhitePawn);

    EXPECT_FALSE(isRookMove(board, { { 4, 4 }, { 4, 0 } }));
}

TEST_F(RulesTest, RookCannotMoveDiagonally)
{
    board.setPiece({ 4, 4 }, Piece::WhiteRook);

    EXPECT_FALSE(isRookMove(board, { { 4, 4 }, { 2, 2 } }));
}

// ----------------------------------------------------
// Knight
// ----------------------------------------------------

TEST_F(RulesTest, KnightMovesInLShape)
{
    board.setPiece({ 4, 4 }, Piece::WhiteKnight);

    EXPECT_TRUE(isKnightMove(board, { { 4, 4 }, { 2, 5 } }));
}

TEST_F(RulesTest, KnightCanJumpPieces)
{
    board.setPiece({ 4, 4 }, Piece::WhiteKnight);
    board.setPiece({ 3, 4 }, Piece::WhitePawn);

    EXPECT_TRUE(isKnightMove(board, { { 4, 4 }, { 2, 5 } }));
}

TEST_F(RulesTest, KnightCannotMoveStraight)
{
    board.setPiece({ 4, 4 }, Piece::WhiteKnight);

    EXPECT_FALSE(isKnightMove(board, { { 4, 4 }, { 4, 6 } }));
}

// ----------------------------------------------------
// Bishop
// ----------------------------------------------------

TEST_F(RulesTest, BishopMovesDiagonally)
{
    board.setPiece({ 4, 4 }, Piece::WhiteBishop);

    EXPECT_TRUE(isBishopMove(board, { { 4, 4 }, { 1, 1 } }));
}

TEST_F(RulesTest, BishopBlocked)
{
    board.setPiece({ 4, 4 }, Piece::WhiteBishop);
    board.setPiece({ 3, 3 }, Piece::WhitePawn);

    EXPECT_FALSE(isBishopMove(board, { { 4, 4 }, { 1, 1 } }));
}

TEST_F(RulesTest, BishopCannotMoveStraight)
{
    board.setPiece({ 4, 4 }, Piece::WhiteBishop);

    EXPECT_FALSE(isBishopMove(board, { { 4, 4 }, { 4, 0 } }));
}

// ----------------------------------------------------
// Queen
// ----------------------------------------------------

TEST_F(RulesTest, QueenMovesHorizontally)
{
    board.setPiece({ 4, 4 }, Piece::WhiteQueen);

    EXPECT_TRUE(isQueenMove(board, { { 4, 4 }, { 4, 0 } }));
}

TEST_F(RulesTest, QueenMovesDiagonally)
{
    board.setPiece({ 4, 4 }, Piece::WhiteQueen);

    EXPECT_TRUE(isQueenMove(board, { { 4, 4 }, { 0, 0 } }));
}

// ----------------------------------------------------
// King
// ----------------------------------------------------

TEST_F(RulesTest, KingMovesOneSquare)
{
    board.setPiece({ 4, 4 }, Piece::WhiteKing);

    EXPECT_TRUE(isKingMove(board, { { 4, 4 }, { 5, 5 } }));
}

TEST_F(RulesTest, KingCannotMoveTwoSquares)
{
    board.setPiece({ 4, 4 }, Piece::WhiteKing);

    EXPECT_FALSE(isKingMove(board, { { 4, 4 }, { 6, 4 } }));
}

// ----------------------------------------------------
// Castling
// ----------------------------------------------------

TEST_F(RulesTest, WhiteKingsideCastleAllowed)
{
    board.setPiece({ 7, 4 }, Piece::WhiteKing);
    board.setPiece({ 7, 7 }, Piece::WhiteRook);

    EXPECT_TRUE(canCastle(board, { { 7, 4 }, { 7, 6 } }, state));
}

TEST_F(RulesTest, WhiteCannotCastleAfterKingMoved)
{
    board.setPiece({ 7, 4 }, Piece::WhiteKing);
    board.setPiece({ 7, 7 }, Piece::WhiteRook);

    state.castling.whiteKingMoved = true;

    EXPECT_FALSE(canCastle(board, { { 7, 4 }, { 7, 6 } }, state));
}

// ----------------------------------------------------
// En Passant
// ----------------------------------------------------

TEST_F(RulesTest, ValidEnPassant)
{
    board.setPiece({ 3, 4 }, Piece::WhitePawn);
    board.setPiece({ 3, 5 }, Piece::BlackPawn);

    state.enPassantTarget = { 2, 5 };

    EXPECT_TRUE(canEnPassant(board, { { 3, 4 }, { 2, 5 } }, state));
}

TEST_F(RulesTest, InvalidEnPassantWithoutTarget)
{
    board.setPiece({ 3, 4 }, Piece::WhitePawn);
    board.setPiece({ 3, 5 }, Piece::BlackPawn);

    EXPECT_FALSE(canEnPassant(board, { { 3, 4 }, { 2, 5 } }, state));
}

// ----------------------------------------------------
// Dispatcher
// ----------------------------------------------------

TEST_F(RulesTest, DispatcherPawn)
{
    board.setPiece({ 6, 4 }, Piece::WhitePawn);

    EXPECT_TRUE(isMoveLegal(board, { { 6, 4 }, { 5, 4 } }));
}

TEST_F(RulesTest, DispatcherRook)
{
    board.setPiece({ 4, 4 }, Piece::WhiteRook);

    EXPECT_TRUE(isMoveLegal(board, { { 4, 4 }, { 4, 0 } }));
}

TEST_F(RulesTest, DispatcherKnight)
{
    board.setPiece({ 4, 4 }, Piece::WhiteKnight);

    EXPECT_TRUE(isMoveLegal(board, { { 4, 4 }, { 2, 5 } }));
}

TEST_F(RulesTest, DispatcherBishop)
{
    board.setPiece({ 4, 4 }, Piece::WhiteBishop);

    EXPECT_TRUE(isMoveLegal(board, { { 4, 4 }, { 1, 1 } }));
}

TEST_F(RulesTest, DispatcherQueen)
{
    board.setPiece({ 4, 4 }, Piece::WhiteQueen);

    EXPECT_TRUE(isMoveLegal(board, { { 4, 4 }, { 0, 0 } }));
}

TEST_F(RulesTest, DispatcherKing)
{
    board.setPiece({ 4, 4 }, Piece::WhiteKing);

    EXPECT_TRUE(isMoveLegal(board, { { 4, 4 }, { 5, 5 } }));
}

TEST_F(RulesTest, DispatcherEmptySquare)
{
    EXPECT_FALSE(isMoveLegal(board, { { 4, 4 }, { 5, 5 } }));
}
