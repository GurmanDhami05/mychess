#include "game.h"
#include "renderer.h"
#include "sdl.h"

Game::~Game()
{
    cleanup();
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
            }
        }

        if (event_.type == SDL_MOUSEBUTTONDOWN &&
            event_.button.button == SDL_BUTTON_LEFT)
        {

            Position clicked{ event_.button.y / TILE_SIZE,
                              event_.button.x / TILE_SIZE };

            if (engine_.handleClick(clicked))
            {
                engine_.update();
            }
        }
    }
}

void Game::renderFrame()
{

    render(renderer_, textures_, engine_.board(), engine_.state());
}

void Game::cleanup()
{
    destroyTextures(textures_);
    cleanupSDL(renderer_, window_);

    renderer_ = nullptr;
    window_ = nullptr;
}
