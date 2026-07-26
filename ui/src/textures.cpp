#include "textures.h"
#include "chess/board.h"

#include <SDL2/SDL_image.h>
#include <array>
#include <iostream>

void loadTextures(Textures &textures, SDL_Renderer *renderer)
{
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

bool checkTexture(const Textures &textures)
{
    for (int i = 0; i < textures.pieceTextures.size(); i++)
    {
        if (i == 6)
        {
            continue;
        }
        if (textures.pieceTextures[i] == nullptr)
        {

            std::cerr << "texture failed to load at index: " << piecesLUT[i]
                      << std::endl;
            return false;
        }
    }
    return true;
}

void destroyTextures(Textures &textures)
{
    for (SDL_Texture *texture : textures.pieceTextures)
    {
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        }
    }
}
