#pragma once

#include <string.h>
#include "Game.hpp"

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    static void InitWriting(const char* chset);

    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int frame);
    static void DrawBackground();

    static void DrawString( int x, int y, const char *text, SDL_Texture *charset, float scale);
    static void DrawInfo(Uint32 WorldTime);
    static void DrawOutro(Uint32 FinishTime);
};




