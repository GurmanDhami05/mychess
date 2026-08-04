#include "chess/perft.h"
#include "chess/chess_engine.h"
#include <iostream>
#include <string>

std::string moveToString(const Move &move)
{
    std::string result;
    result += static_cast<char>('a' + move.from.col);
    result += std::to_string(8 - move.from.row);
    result += static_cast<char>('a' + move.to.col);
    result += std::to_string(8 - move.to.row);
    return result;
}

uint64_t perft(ChessEngine &engine, int depth)
{
    if (depth == 0)
    {
        return 1;
    }
    uint64_t nodes = 0;
    auto moves = engine.legalMoves();

    for (const Move &move : moves)
    {
        if (!engine.makeMove(move))
        {
            continue;
        }

        nodes += perft(engine, depth - 1);
        engine.undoLastMove();
    }
    return nodes;
}

uint64_t perftDivide(ChessEngine &engine, int depth)
{
    if (depth == 0)
    {
        return 1;
    }
    uint64_t nodes = 0;
    auto moves = engine.legalMoves();

    for (const Move &move : moves)
    {
        if (!engine.makeMove(move))
        {
            continue;
        }
        uint64_t subtree = perft(engine, depth - 1);
        std::cout << moveToString(move) << " : " << subtree << '\n';

        nodes += subtree;
        engine.undoLastMove();
    }
    return nodes;
}
