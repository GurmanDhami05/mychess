#include <gtest/gtest.h>

#include "chess/check.h"
#include "chess/chess_engine.h"
#include "chess/legal_moves.h"
#include "chess/perft.h"
#include "chess/piece.h"

class EngineTest : public ::testing::Test
{
  protected:
    ChessEngine engine;

    static Position square(char file, char rank)
    {
        return { 8 - (rank - '0'), file - 'a' };
    }

    static Move parseMove(const std::string &move)
    {
        EXPECT_EQ(move.length(), 4);

        return { square(move[0], move[1]), square(move[2], move[3]) };
    }

    void play(const std::string &move)
    {
        ASSERT_TRUE(engine.makeMove(parseMove(move)))
            << "Failed move: " << move;
    }

    void load(const std::string &fen)
    {
        ASSERT_TRUE(engine.loadFEN(fen));
    }

    void expectFEN(const std::string &fen)
    {
        EXPECT_EQ(engine.exportFEN(), fen);
    }
};

TEST_F(EngineTest, InitialPositionPerftDepth1)
{
    EXPECT_EQ(perft(engine, 1), 20);
}

TEST_F(EngineTest, InitialPositionPerftDepth2)
{
    EXPECT_EQ(perft(engine, 2), 400);
}

TEST_F(EngineTest, MakeMoveMovesPiece)
{
    play("e2e4");

    EXPECT_EQ(engine.board().pieceAt(square('e', '4')), Piece::WhitePawn);

    EXPECT_EQ(engine.board().pieceAt(square('e', '2')), Piece::None);

    EXPECT_EQ(engine.turn(), Turn::Black);
}

TEST_F(EngineTest, UndoMoveRestoresPosition)
{
    std::string original = engine.exportFEN();

    play("e2e4");

    engine.undoLastMove();

    EXPECT_EQ(engine.exportFEN(), original);
}

TEST_F(EngineTest, CapturePiece)
{
    load("8/8/8/3p4/4P3/8/8/8 w - - 0 1");

    play("e4d5");

    EXPECT_EQ(engine.board().pieceAt(square('d', '5')), Piece::WhitePawn);

    EXPECT_EQ(engine.board().pieceAt(square('e', '4')), Piece::None);
}

TEST_F(EngineTest, RejectIllegalMove)
{
    EXPECT_FALSE(engine.makeMove(parseMove("e2e5")));

    EXPECT_EQ(engine.board().pieceAt(square('e', '2')), Piece::WhitePawn);
}

TEST_F(EngineTest, TurnAlternates)
{
    EXPECT_EQ(engine.turn(), Turn::White);

    play("e2e4");

    EXPECT_EQ(engine.turn(), Turn::Black);

    play("e7e5");

    EXPECT_EQ(engine.turn(), Turn::White);
}

TEST_F(EngineTest, DoublePawnMoveCreatesEnPassantTarget)
{
    play("e2e4");

    EXPECT_TRUE(engine.state().enPassantTarget.isValid());

    EXPECT_EQ(engine.state().enPassantTarget, square('e', '3'));
}

TEST_F(EngineTest, PawnMoveResetsHalfMoveClock)
{
    play("e2e4");

    EXPECT_EQ(engine.state().halfMoveClock, 0);
}

TEST_F(EngineTest, QuietMoveIncrementsHalfMoveClock)
{
    play("g1f3");

    EXPECT_EQ(engine.state().halfMoveClock, 1);
}

TEST_F(EngineTest, FullMoveNumberIncrementsAfterBlackMove)
{
    EXPECT_EQ(engine.state().fullMoveNumber, 1);

    play("e2e4");

    EXPECT_EQ(engine.state().fullMoveNumber, 1);

    play("e7e5");

    EXPECT_EQ(engine.state().fullMoveNumber, 2);
}
TEST_F(EngineTest, KingsideCastle)
{
    load("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");

    play("e1g1");

    EXPECT_EQ(engine.board().pieceAt(square('g', '1')), Piece::WhiteKing);
    EXPECT_EQ(engine.board().pieceAt(square('f', '1')), Piece::WhiteRook);

    EXPECT_EQ(engine.board().pieceAt(square('e', '1')), Piece::None);
    EXPECT_EQ(engine.board().pieceAt(square('h', '1')), Piece::None);
}

TEST_F(EngineTest, QueensideCastle)
{
    load("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");

    play("e1c1");

    EXPECT_EQ(engine.board().pieceAt(square('c', '1')), Piece::WhiteKing);
    EXPECT_EQ(engine.board().pieceAt(square('d', '1')), Piece::WhiteRook);

    EXPECT_EQ(engine.board().pieceAt(square('a', '1')), Piece::None);
    EXPECT_EQ(engine.board().pieceAt(square('e', '1')), Piece::None);
}

TEST_F(EngineTest, UndoCastle)
{
    load("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");

    std::string original = engine.exportFEN();

    play("e1g1");

    engine.undoLastMove();

    EXPECT_EQ(engine.exportFEN(), original);
}

TEST_F(EngineTest, Promotion)
{
    load("8/P7/8/8/8/8/8/k6K w - - 0 1");

    play("a7a8");

    EXPECT_EQ(engine.board().pieceAt(square('a', '8')), Piece::WhiteQueen);
}

TEST_F(EngineTest, UndoPromotion)
{
    load("8/P7/8/8/8/8/8/k6K w - - 0 1");

    std::string original = engine.exportFEN();

    play("a7a8");

    engine.undoLastMove();

    EXPECT_EQ(engine.exportFEN(), original);
}

TEST_F(EngineTest, EnPassantCapture)
{
    load("8/8/8/3pP3/8/8/8/8 w - d6 0 1");

    play("e5d6");

    EXPECT_EQ(engine.board().pieceAt(square('d', '6')), Piece::WhitePawn);
    EXPECT_EQ(engine.board().pieceAt(square('d', '5')), Piece::None);
}

TEST_F(EngineTest, UndoEnPassant)
{
    load("8/8/8/3pP3/8/8/8/8 w - d6 0 1");

    std::string original = engine.exportFEN();

    play("e5d6");

    engine.undoLastMove();

    EXPECT_EQ(engine.exportFEN(), original);
}

TEST_F(EngineTest, CastlingRightsLostAfterKingMove)
{
    play("e2e4");
    play("e7e5");
    play("e1e2");

    EXPECT_FALSE(engine.state().castling.whiteCanCastleKingside());
    EXPECT_FALSE(engine.state().castling.whiteCanCastleQueenside());
}

TEST_F(EngineTest, CastlingRightsLostAfterRookMove)
{
    load("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");

    play("h1h2");

    EXPECT_FALSE(engine.state().castling.whiteCanCastleKingside());
    EXPECT_TRUE(engine.state().castling.whiteCanCastleQueenside());
}

TEST_F(EngineTest, FoolMateCheckmate)
{
    play("f2f3");
    play("e7e5");
    play("g2g4");
    play("d8h4");
    EXPECT_TRUE(isKingInCheck(engine.board(), Turn::White));

    EXPECT_TRUE(isSquareAttacked(engine.board(),
                                 getKingPosition(engine.board(), Turn::White),
                                 Turn::Black));

    EXPECT_TRUE(
        isSquareAttacked(engine.board(), square('e', '1'), Turn::Black));

    std::cout << engine.exportFEN() << '\n';

    std::cout << "White in check : " << engine.state().whiteKing.inCheck
              << '\n';

    std::cout << "Checkmate      : " << engine.state().checkmate << '\n';

    std::cout << "Stalemate      : " << engine.state().stalemate << '\n';

    auto moves = engine.legalMoves();

    std::cout << "Legal moves: " << moves.size() << '\n';

    EXPECT_TRUE(engine.state().checkmate);
}
TEST(Check, QueenAttacksKing)
{
    Board board;
    board.clear();

    board.setPiece({ 7, 4 }, Piece::WhiteKing);  // e1
    board.setPiece({ 4, 7 }, Piece::BlackQueen); // h4

    EXPECT_TRUE(isKingInCheck(board, Turn::White));
}

TEST_F(EngineTest, DetectStalemate)
{
    load("7k/5Q2/6K1/8/8/8/8/8 b - - 0 1");

    EXPECT_TRUE(engine.state().stalemate);
}

TEST_F(EngineTest, DetectCheck)
{
    load("4k3/8/8/8/8/8/4R3/4K3 b - - 0 1");

    EXPECT_TRUE(engine.state().blackKing.inCheck);
}

TEST_F(EngineTest, UndoSequenceOfMoves)
{
    std::string original = engine.exportFEN();

    play("e2e4");
    play("e7e5");
    play("g1f3");
    play("b8c6");
    play("f1c4");

    engine.undoLastMove();
    engine.undoLastMove();
    engine.undoLastMove();
    engine.undoLastMove();
    engine.undoLastMove();

    EXPECT_EQ(engine.exportFEN(), original);
}

TEST_F(EngineTest, FENAfterOpeningSequence)
{
    play("e2e4");
    play("e7e5");
    play("g1f3");
    play("b8c6");

    EXPECT_EQ(
        engine.exportFEN(),
        "r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3");
}
