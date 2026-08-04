#include <gtest/gtest.h>

#include "chess/board.h"
#include "chess/fen.h"
#include "chess/game_state.h"

class FENTest : public ::testing::Test
{
  protected:
    Board board;
    GameState state;
    Turn turn = Turn::White;
};

TEST_F(FENTest, RoundTrip)
{
    std::string original =
        "r3k2r/pppq1ppp/2npbn2/3Np3/2B1P3/2N5/PPP2PPP/R1BQ1RK1 w kq - 3 10";

    ASSERT_TRUE(FEN::loadFEN(board, turn, state, original));

    EXPECT_EQ(FEN::exportFEN(board, turn, state), original);
}

TEST_F(FENTest, StartingPosition)
{
    const std::string fen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    ASSERT_TRUE(FEN::loadFEN(board, turn, state, fen));

    EXPECT_EQ(FEN::exportFEN(board, turn, state), fen);
}

TEST_F(FENTest, EmptyBoard)
{
    const std::string fen = "8/8/8/8/8/8/8/8 w - - 0 1";

    ASSERT_TRUE(FEN::loadFEN(board, turn, state, fen));

    EXPECT_EQ(FEN::exportFEN(board, turn, state), fen);
}

TEST_F(FENTest, CastlingRights)
{
    const std::string fen = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1";

    ASSERT_TRUE(FEN::loadFEN(board, turn, state, fen));

    EXPECT_EQ(FEN::exportFEN(board, turn, state), fen);
}

TEST_F(FENTest, EnPassant)
{
    const std::string fen = "8/8/8/3pP3/8/8/8/8 w - d6 0 1";

    ASSERT_TRUE(FEN::loadFEN(board, turn, state, fen));

    EXPECT_EQ(FEN::exportFEN(board, turn, state), fen);
}

TEST_F(FENTest, MoveCounters)
{
    turn = Turn::Black; // Only override when different from fixture

    const std::string fen = "8/8/8/8/8/8/8/8 b - - 47 82";

    ASSERT_TRUE(FEN::loadFEN(board, turn, state, fen));

    EXPECT_EQ(FEN::exportFEN(board, turn, state), fen);
}

TEST_F(FENTest, InvalidPiece)
{
    EXPECT_FALSE(
        FEN::loadFEN(board, turn, state, "x7/8/8/8/8/8/8/8 w - - 0 1"));
}

TEST_F(FENTest, InvalidTurn)
{
    EXPECT_FALSE(FEN::loadFEN(board, turn, state, "8/8/8/8/8/8/8/8 x - - 0 1"));
}

TEST_F(FENTest, InvalidCastlingRights)
{
    EXPECT_FALSE(
        FEN::loadFEN(board, turn, state, "8/8/8/8/8/8/8/8 w ABC - 0 1"));
}

TEST_F(FENTest, InvalidEnPassant)
{
    EXPECT_FALSE(
        FEN::loadFEN(board, turn, state, "8/8/8/8/8/8/8/8 w - z9 0 1"));
}

TEST_F(FENTest, MissingFields)
{
    EXPECT_FALSE(FEN::loadFEN(board, turn, state, "8/8/8/8/8/8/8/8"));
}

TEST_F(FENTest, ExtraFields)
{
    EXPECT_FALSE(
        FEN::loadFEN(board, turn, state, "8/8/8/8/8/8/8/8 w - - 0 1 extra"));
}
