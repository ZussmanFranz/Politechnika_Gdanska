#include "Map.hpp"
#include "TextureManager.hpp"
//#include "Entities.hpp"

int lvl1[12][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,2,1,1,2,1,1,1,1},
    {1,1,1,1,1,1,0,0,2,0,0,2,0,0,2,0},
    {0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0},
    {0,0,0,0,0,0,0,0,2,1,1,1,0,0,1,1},
    {2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,2,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,2,0,0,0,0,0,0,1,1,1,1,1,1,1},
    {0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map()
{
    dark = TextureManager::LoadTexture("assets/dark.bmp");
    platform = TextureManager::LoadTexture("assets/platform.bmp");
    stairs = TextureManager::LoadTexture("assets/stairs.bmp");

    LoadMap(lvl1);
    src.x = src.y = 0;
    src.w = dest.w = 64;
    src.h = dest.h = 64;
}

void Map::LoadMap(int arr[12][16])
{
    for (int row = 0; row < 12; row++)
    {
        for (int column = 0; column < 16; column++)
        {
            map[row][column] = arr[row][column];
        }
    }
}

void Map::EntifyMap(Entities* entities)
{
    int type = 0;
    int x, y;

    for (int row = 0; row < 12; row++)
    {
        for (int column = 0; column < 16; column++)
        {
            type = map[row][column];

            x = column * 64;
            y = row * 64;

            switch (type)
            {
            case 1:
                entities->CreateObject("assets/platform.bmp", x, y, 0, 'O', 1);
                break;
            case 2:
                entities->CreateObject("assets/stairs.bmp", x, y, 0, 'S', 1);
                break;
            case 3:
                entities->CreateObject("assets/exit.bmp", x, y, 0, 'E', 1);
                break;
            default:
                break;
            }
        }
    }
}

void Map::DrawMap()
{
    int type = 0;

    for (int row = 0; row < 12; row++)
    {
        for (int column = 0; column < 16; column++)
        {
            type = map[row][column];

            dest.x = column * 64;
            dest.y = row * 64;

            switch (type)
            {
            case 0:
                TextureManager::Draw(dark, src, dest, 1);
                break;
            case 1:
                TextureManager::Draw(platform, src, dest, 1);
                break;
            case 2:
                TextureManager::Draw(stairs, src, dest, 1);
                break;
            default:
                break;
            }
        }
    }
}