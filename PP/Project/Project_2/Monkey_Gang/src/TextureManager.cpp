#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer *ren)
{
    SDL_Surface* tempSurface = SDL_LoadBMP(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}