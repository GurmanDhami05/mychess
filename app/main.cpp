#include "chess/perft.h"
#include "game.h"
#include <iostream>

int main()
{

    Game game;
    // std::cout << perft(game.engine(), 1) << std::endl;
    if (!game.initialize())
    {
        return 1;
    }
    game.run();

    return 0;
}
