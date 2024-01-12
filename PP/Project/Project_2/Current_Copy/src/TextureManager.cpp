#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
    SDL_Surface* tempSurface = SDL_LoadBMP(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int frame)
{
    src.x = src.w * (frame - 1);
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

void TextureManager::DrawBackground()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

    SDL_Rect rect;
    rect.x = 0; 
    rect.y = 0; 
    rect.w = Game::SCREEN_WIDTH; 
    rect.h = Game::SCREEN_HEIGHT; 

    SDL_RenderFillRect(Game::renderer, &rect);

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}