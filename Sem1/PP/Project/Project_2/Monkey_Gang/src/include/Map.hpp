#pragma once

#include "Game.hpp"
#include "Entities.hpp"

class Map
{
public:

    Map();
    ~Map();

    void LoadMap(int arr[12][16]);
    void EntifyMap(Entities* entities);
    void DrawMap();

private:
    SDL_Rect src, dest;

    SDL_Texture* dark;
    SDL_Texture* platform;
    SDL_Texture* stairs;

    int map[12][16];
};
