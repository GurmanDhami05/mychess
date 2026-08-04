#include <gtest/gtest.h>

#include <chess/board.h>
#include <chess/piece.h>

class BoardTest : public ::testing::Test
{
  protected:
    Board board;

    void SetUp() override
    {
        board.clear();
    }
};

TEST(Board, InitializesStartingPosition)
{
    Board board;

    EXPECT_EQ(board.pieceAt({ 0, 0 }), Piece::BlackRook);
    EXPECT_EQ(board.pieceAt({ 0, 4 }), Piece::BlackKing);
    EXPECT_EQ(board.pieceAt({ 0, 7 }), Piece::BlackRook);

    EXPECT_EQ(board.pieceAt({ 1, 0 }), Piece::BlackPawn);
    EXPECT_EQ(board.pieceAt({ 1, 7 }), Piece::BlackPawn);

    EXPECT_EQ(board.pieceAt({ 6, 0 }), Piece::WhitePawn);
    EXPECT_EQ(board.pieceAt({ 6, 7 }), Piece::WhitePawn);

    EXPECT_EQ(board.pieceAt({ 7, 0 }), Piece::WhiteRook);
    EXPECT_EQ(board.pieceAt({ 7, 4 }), Piece::WhiteKing);
    EXPECT_EQ(board.pieceAt({ 7, 7 }), Piece::WhiteRook);

    EXPECT_EQ(board.pieceAt({ 4, 4 }), Piece::None);
}

TEST_F(BoardTest, SetPieceStoresPiece)
{
    Position pos{ 3, 4 };

    board.setPiece(pos, Piece::WhiteQueen);

    EXPECT_EQ(board.pieceAt(pos), Piece::WhiteQueen);
}

TEST_F(BoardTest, SetPieceOverwritesExistingPiece)
{
    Position pos{ 4, 2 };

    board.setPiece(pos, Piece::WhitePawn);
    board.setPiece(pos, Piece::BlackKnight);

    EXPECT_EQ(board.pieceAt(pos), Piece::BlackKnight);
}

TEST_F(BoardTest, ClearRemovesAllPieces)
{
    board.setPiece({ 0, 0 }, Piece::WhiteKing);
    board.setPiece({ 4, 4 }, Piece::BlackQueen);
    board.setPiece({ 7, 7 }, Piece::WhitePawn);

    board.clear();

    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            EXPECT_EQ(board.pieceAt({ row, col }), Piece::None);
        }
    }
}

TEST_F(BoardTest, IsEmptyReturnsTrueForEmptySquare)
{
    EXPECT_TRUE(board.isEmpty({ 2, 2 }));
}

TEST_F(BoardTest, IsEmptyReturnsFalseForOccupiedSquare)
{
    board.setPiece({ 2, 2 }, Piece::WhiteKnight);

    EXPECT_FALSE(board.isEmpty({ 2, 2 }));
}

TEST_F(BoardTest, IsInsideReturnsTrueForValidSquares)
{
    EXPECT_TRUE(board.isInside({ 0, 0 }));
    EXPECT_TRUE(board.isInside({ 7, 7 }));
    EXPECT_TRUE(board.isInside({ 3, 5 }));
}

TEST_F(BoardTest, IsInsideReturnsFalseForInvalidSquares)
{
    EXPECT_FALSE(board.isInside({ -1, 0 }));
    EXPECT_FALSE(board.isInside({ 0, -1 }));
    EXPECT_FALSE(board.isInside({ 8, 0 }));
    EXPECT_FALSE(board.isInside({ 0, 8 }));
}

TEST_F(BoardTest, MovePieceMovesPiece)
{
    Move move{ { 6, 4 }, { 4, 4 } };

    board.setPiece(move.from, Piece::WhitePawn);

    board.movePiece(move);

    EXPECT_EQ(board.pieceAt(move.from), Piece::None);
    EXPECT_EQ(board.pieceAt(move.to), Piece::WhitePawn);
}

TEST_F(BoardTest, UndoMoveRestoresBoard)
{
    Move move{ { 6, 4 }, { 4, 4 } };

    board.setPiece(move.from, Piece::WhitePawn);

    board.movePiece(move);
    board.undoMove(move, Piece::None);

    EXPECT_EQ(board.pieceAt(move.from), Piece::WhitePawn);
    EXPECT_EQ(board.pieceAt(move.to), Piece::None);
}

TEST_F(BoardTest, UndoMoveRestoresCapturedPiece)
{
    Move move{ { 6, 4 }, { 4, 4 } };

    board.setPiece(move.from, Piece::WhitePawn);
    board.setPiece(move.to, Piece::BlackKnight);

    board.movePiece(move);
    board.undoMove(move, Piece::BlackKnight);

    EXPECT_EQ(board.pieceAt(move.from), Piece::WhitePawn);
    EXPECT_EQ(board.pieceAt(move.to), Piece::BlackKnight);
}
