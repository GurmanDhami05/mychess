#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>
#include <iostream>

const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 480;
const int TILE_SIZE = 60;
const int BOARD_SIZE = 8;
const int EMPTY = 0;

struct Textures {
    std::array<SDL_Texture *, 13> pieceTextures;
};

const std::array<std::string, 13> piecesLUT = {
    "black_king",   // index 0
    "black_queen",  // index 1
    "black_bishop", // index 2
    "black_knight", // index 3
    "black_rook",   // index 4
    "black_pawn",   // index 5
    "",             // index 6 (empty)
    "white_pawn",   // index 7
    "white_rook",   // index 8
    "white_knight", // index 9
    "white_bishop", // index 10
    "white_queen",  // index 11
    "white_king"    // index 12
};

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed! SDL Error: " << SDL_GetError()
                  << std::endl;
        return false;
    }
    return true;
}

bool initalizeSDLImage() {
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_Img initialization failed! SDL Error: "
                  << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Window *createWindow() {
    SDL_Window *window = SDL_CreateWindow("Chess",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          0);

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL Error: "
                  << SDL_GetError() << std::endl;
        return nullptr;
    }
    return window;
}

SDL_Renderer *createRenderer(SDL_Window *window) {
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "Could not create renderer! SDL Error: " << SDL_GetError()
                  << std::endl;
        return nullptr;
    }

    return renderer;
}

void drawBoard(SDL_Renderer *renderer);
void drawPieces(SDL_Renderer *renderer,
                const Textures &textures,
                const int board[BOARD_SIZE][BOARD_SIZE]);

void render(SDL_Renderer *renderer,
            const Textures &textures,
            const int board[BOARD_SIZE][BOARD_SIZE]) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // drawing chess board
    drawBoard(renderer);
    drawPieces(renderer, textures, board);

    SDL_RenderPresent(renderer);
}

void drawBoard(SDL_Renderer *renderer) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if ((row + col) % 2 == 0) {

                SDL_SetRenderDrawColor(renderer, 74, 117, 89, 255);

            } else {

                SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255);
            }

            SDL_Rect tile = {
                col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE
            };

            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

void loadTextures(Textures &textures, SDL_Renderer *renderer) {
    textures.pieceTextures[0] =
        IMG_LoadTexture(renderer, "./assets/Chess_kdt60.png"); // black_king
    textures.pieceTextures[1] =
        IMG_LoadTexture(renderer, "./assets/Chess_qdt60.png"); // black_queen
    textures.pieceTextures[2] =
        IMG_LoadTexture(renderer, "./assets/Chess_bdt60.png"); // black_bishop
    textures.pieceTextures[3] =
        IMG_LoadTexture(renderer, "./assets/Chess_ndt60.png"); // black_knight
    textures.pieceTextures[4] =
        IMG_LoadTexture(renderer, "./assets/Chess_rdt60.png"); // black_rook
    textures.pieceTextures[5] =
        IMG_LoadTexture(renderer, "./assets/Chess_pdt60.png"); // black_pawn

    textures.pieceTextures[6] = nullptr;

    textures.pieceTextures[7] =
        IMG_LoadTexture(renderer, "./assets/Chess_plt60.png"); // white_pawn
    textures.pieceTextures[8] =
        IMG_LoadTexture(renderer, "./assets/Chess_rlt60.png"); // white_rook
    textures.pieceTextures[9] =
        IMG_LoadTexture(renderer, "./assets/Chess_nlt60.png"); // white_knight
    textures.pieceTextures[10] =
        IMG_LoadTexture(renderer, "./assets/Chess_blt60.png"); // white_bishop
    textures.pieceTextures[11] =
        IMG_LoadTexture(renderer, "./assets/Chess_qlt60.png"); // white_queen
    textures.pieceTextures[12] =
        IMG_LoadTexture(renderer, "./assets/Chess_klt60.png"); // white_king
}

bool checkTexture(const Textures &textures) {
    for (int i = 0; i < textures.pieceTextures.size(); i++) {
        if (i == 6) {
            continue;
        }
        if (textures.pieceTextures[i] == nullptr) {

            std::cerr << "texture failed to load at index: " << piecesLUT[i]
                      << std::endl;
            return false;
        }
    }
    return true;
}

int pieceToIndex(int piece) { return piece + 6; }

void drawPieces(SDL_Renderer *renderer,
                const Textures &textures,
                const int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {

            int piece = board[row][col];

            if (piece == EMPTY) {
                continue;
            }

            SDL_Rect pieceRect = {
                col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE
            };

            SDL_Texture *pieceTexture =
                textures.pieceTextures[pieceToIndex(piece)];

            if (pieceTexture == nullptr) {
                continue;
            }

            SDL_RenderCopy(renderer, pieceTexture, nullptr, &pieceRect);
        }
    }
}

void destroyTextures(Textures &textures) {
    for (SDL_Texture *texture : textures.pieceTextures) {
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
    }
}

void initalizeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (row == 1) {
                board[row][col] = -1;
            } else if (row == 6) {
                board[row][col] = 1;
            } else {
                board[row][col] = EMPTY;
            }
        }
    }

    // black pieces
    board[0][0] = -2; // b_rook
    board[0][1] = -3; // b_knight
    board[0][2] = -4; // b_bishop
    board[0][3] = -5; // b_queen
    board[0][4] = -6; // b_king
    board[0][5] = -4; // b_bishop
    board[0][6] = -3; // b_knight
    board[0][7] = -2; // b_rook

    // white pieces
    board[7][0] = 2; // w_rook
    board[7][1] = 3; // w_knight
    board[7][2] = 4; // w_bishop
    board[7][3] = 5; // w_queen
    board[7][4] = 6; // w_king
    board[7][5] = 4; // w_bishop
    board[7][6] = 3; // w_knight
    board[7][7] = 2; // w_rook
}

void printBoard(const int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            std::cout << board[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {

    int board[BOARD_SIZE][BOARD_SIZE];
    initalizeBoard(board);

    if (!initializeSDL()) {
        return 1;
    }

    if (!initalizeSDLImage()) {
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

    bool isRunning = true;
    SDL_Event e;

    while (isRunning) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        render(renderer, textures, board);
    }

    destroyTextures(textures);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
