#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 60;
const int BOARD_SIZE = 8;
const int EMPTY = 0;

struct Textures {
    std::array<SDL_Texture *, 13> pieces{};
};

SDL_Window *initWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError()
                  << std::endl;
        return nullptr;
    }

    SDL_Window *window = SDL_CreateWindow("Chess",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        return nullptr;
    }
    return window;
}

SDL_Renderer *initRenderer(SDL_Window *window) {

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Renderer Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return renderer;
}

bool initSDLImage() {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

void drawBoard(SDL_Renderer *renderer) {

    // Draw chess board
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Alternate colors
            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);
            }

            SDL_Rect square = {
                col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE
            };

            SDL_RenderFillRect(renderer, &square);
        }
    }
}

int textureIndex(int piece) { return piece + 6; }

bool loadTexture(SDL_Renderer *renderer,
                 Textures &textures,
                 int piece,
                 const std::string &path) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

    if (texture == nullptr) {
        std::cout << "Could not load " << path << ": " << IMG_GetError()
                  << std::endl;
        return false;
    }

    textures.pieces[textureIndex(piece)] = texture;
    return true;
}

bool loadPieceTextures(SDL_Renderer *renderer, Textures &textures) {
    return loadTexture(renderer, textures, 1, "assets/Chess_plt60.png") &&
           loadTexture(renderer, textures, 2, "assets/Chess_rlt60.png") &&
           loadTexture(renderer, textures, 3, "assets/Chess_nlt60.png") &&
           loadTexture(renderer, textures, 4, "assets/Chess_blt60.png") &&
           loadTexture(renderer, textures, 5, "assets/Chess_qlt60.png") &&
           loadTexture(renderer, textures, 6, "assets/Chess_klt60.png") &&
           loadTexture(renderer, textures, -1, "assets/Chess_pdt60.png") &&
           loadTexture(renderer, textures, -2, "assets/Chess_rdt60.png") &&
           loadTexture(renderer, textures, -3, "assets/Chess_ndt60.png") &&
           loadTexture(renderer, textures, -4, "assets/Chess_bdt60.png") &&
           loadTexture(renderer, textures, -5, "assets/Chess_qdt60.png") &&
           loadTexture(renderer, textures, -6, "assets/Chess_kdt60.png");
}

void destroyTextures(Textures &textures) {
    for (SDL_Texture *texture : textures.pieces) {
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
    }
}

void drawPieces(SDL_Renderer *renderer,
                const int board[BOARD_SIZE][BOARD_SIZE],
                const Textures &textures) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            int piece = board[row][col];

            if (piece == EMPTY) {
                continue;
            }

            SDL_Texture *texture = textures.pieces[textureIndex(piece)];

            if (texture == nullptr) {
                continue;
            }

            SDL_Rect destination = {
                col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE
            };

            SDL_RenderCopy(renderer, texture, nullptr, &destination);
        }
    }
}

void render(SDL_Renderer *renderer,
            const int board[BOARD_SIZE][BOARD_SIZE],
            const Textures &textures) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    drawBoard(renderer);
    drawPieces(renderer, board, textures);

    SDL_RenderPresent(renderer);
}

void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = EMPTY;
        }
    }

    for (int col = 0; col < BOARD_SIZE; col++) {
        board[1][col] = -1;
        board[6][col] = 1;
    }

    // Black back row
    board[0][0] = -2; // rook
    board[0][1] = -3; // knight
    board[0][2] = -4; // bishop
    board[0][3] = -5; // queen
    board[0][4] = -6; // king
    board[0][5] = -4; // bishop
    board[0][6] = -3; // knight
    board[0][7] = -2; // rook

    // White back row
    board[7][0] = 2; // rook
    board[7][1] = 3; // knight
    board[7][2] = 4; // bishop
    board[7][3] = 5; // queen
    board[7][4] = 6; // king
    board[7][5] = 4; // bishop
    board[7][6] = 3; // knight
    board[7][7] = 2; // rook
}

void printBoard(const int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            std::cout << board[row][col] << "\t";
        }
        std::cout << '\n';
    }
}

int main() {

    int board[BOARD_SIZE][BOARD_SIZE];
    initializeBoard(board);

    SDL_Window *window = initWindow();

    if (!window) {
        return 1;
    }

    SDL_Renderer *renderer = initRenderer(window);

    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (!initSDLImage()) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Textures textures;
    if (!loadPieceTextures(renderer, textures)) {
        destroyTextures(textures);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        render(renderer, board, textures);
    }

    destroyTextures(textures);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
