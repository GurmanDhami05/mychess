#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mygame/board.h"
#include "mygame/game.h"
#include "mygame/input.h"
#include "mygame/renderer.h"
#include "mygame/sdl.h"
#include "mygame/textures.h"

int main() {

    int board[BOARD_SIZE][BOARD_SIZE];
    initializeBoard(board);

    if (!initializeSDL()) {
        return 1;
    }

    if (!initializeSDLImage()) {
        return 1;
    }

    SDL_Window *window = createWindow();

    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = createRenderer(window);

    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Textures textures;
    loadTextures(textures, renderer);
    if (!checkTexture(textures)) {
        destroyTextures(textures);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    PieceSelected selection;

    Turn currentTurn = Turn::White;

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN &&
                event.button.button == SDL_BUTTON_LEFT) {

                int mouseX = event.button.x;
                int mouseY = event.button.y;

                handleLeftClick(mouseX, mouseY, board, selection, currentTurn);
            }
        }

        render(renderer, textures, board, selection);
    }

    destroyTextures(textures);
    cleanupSDL(renderer, window);
    return 0;
}
