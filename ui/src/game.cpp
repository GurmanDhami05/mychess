#include "game.h"
#include "chess/legal_moves.h"
#include "chess/piece.h"
#include "renderer.h"
#include "sdl.h"
#include <iostream>

Game::~Game()
{
    cleanup();
}

ChessEngine &Game::engine()
{
    return engine_;
}

bool Game::initialize()
{

    if (!initializeSDL())
    {
        return false;
    }
    if (!initializeSDLImage())
    {
        return false;
    }

    window_ = createWindow();
    if (!window_)
    {
        cleanup();
        return false;
    }

    renderer_ = createRenderer(window_);
    if (!renderer_)
    {
        cleanup();
        return false;
    }

    loadTextures(textures_, renderer_);
    if (!checkTexture(textures_))
    {
        cleanup();
        return false;
    }
    return true;
}

void Game::run()
{
    running_ = true;

    while (running_)
    {

        handleEvents();
        renderFrame();
    }
}

void Game::handleEvents()
{

    while (SDL_PollEvent(&event_))
    {
        if (event_.type == SDL_QUIT)
        {
            running_ = false;
        }

        if (event_.type == SDL_KEYDOWN)
        {
            if ((SDL_GetModState() & KMOD_CTRL) &&
                event_.key.keysym.sym == SDLK_z)
            {
                engine_.undoLastMove();
                clearSelection();
            }
        }

        if (event_.type == SDL_MOUSEBUTTONDOWN &&
            event_.button.button == SDL_BUTTON_LEFT)
        {

            Position clicked{ event_.button.y / TILE_SIZE,
                              event_.button.x / TILE_SIZE };

            if (handleClick(clicked))
            {
                engine_.update();
            }
        }
    }
}

void Game::renderFrame()
{

    render(renderer_, textures_, engine_, uiState_);
}

void Game::cleanup()
{
    destroyTextures(textures_);
    cleanupSDL(renderer_, window_);

    renderer_ = nullptr;
    window_ = nullptr;
}
bool Game::handleClick(Position clicked)
{

    if (engine_.state().checkmate || engine_.state().stalemate)
    {
        return false;
    }

    int piece = engine_.board().pieceAt(clicked);

    if (!Piece::isPlayerPiece(piece, engine_.turn()) &&
        uiState_.selection.selected)
    {
        MoveInfo info{ Move{ uiState_.selection.position, clicked } };

        if (engine_.makeMove(info.move))
        {

            clearSelection();
            return true;
        }
        return false;
    }
    // if no piece is selected then first click
    else if (Piece::isPlayerPiece(piece, engine_.turn()))
    {
        selectPiece(clicked);
    }

    return false;
}

void Game::selectPiece(const Position pos)
{
    uiState_.selection.selected = true;
    uiState_.selection.position = pos;

    uiState_.legalMoves =
        getLegalMoves(engine_.board(), pos, engine_.turn(), engine_.state());
}

void Game::clearSelection()
{
    uiState_.selection.selected = false;
    uiState_.selection.position = { -1, -1 };
    uiState_.legalMoves.clear();
}
