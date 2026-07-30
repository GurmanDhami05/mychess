#include <gtest/gtest.h>

#include "chess/board.h"
#include "chess/fen.h"
#include "chess/game_state.h"

TEST(FEN, RoundTrip)
{
    Board board;
    GameState state;
    Turn turn;

    std::string original =
        "r3k2r/pppq1ppp/2npbn2/3Np3/2B1P3/2N5/PPP2PPP/R1BQ1RK1 w kq - 3 10";

    ASSERT_TRUE(FEN::loadFEN(board, turn, state, original));

    EXPECT_EQ(FEN::exportFEN(board, turn, state), original);
}
