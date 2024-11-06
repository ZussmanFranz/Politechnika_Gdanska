#include "time.h"
#include "Map.hpp"
#include "TextureManager.hpp"

int lvl1[12][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,1,1,1,1,2,1,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0},
    {0,0,1,1,2,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,2,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0},
    {0,1,2,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

int lvl2[12][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,2,2,0},
    {0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,2,2,0,0,0,0,2,2,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,0,2,2,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

int lvl3[12][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,2,0,2,0},
    {1,1,0,0,0,0,0,0,0,0,2,0,2,0,0,0},
    {0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0},
    {0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0},
    {0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0},
    {0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0},
    {2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};


Map::Map()
{
    dark = TextureManager::LoadTexture("assets/dark.bmp");
    platform = TextureManager::LoadTexture("assets/platform.bmp");
    stairs = TextureManager::LoadTexture("assets/stairs.bmp");

    src.x = src.y = 0;
    src.w = dest.w = 64;
    src.h = dest.h = 64;

    srand(time(NULL)); //random initialized
}

void Map::LoadMap(int lvl)
{
    switch (lvl)
    {
    case 1:
        for (int row = 0; row < 12; row++)
        {
            for (int column = 0; column < 16; column++)
            {
                map[row][column] = lvl1[row][column];
            }
        }   
        break;
    case 2:
        for (int row = 0; row < 12; row++)
        {
            for (int column = 0; column < 16; column++)
            {
                map[row][column] = lvl2[row][column];
            }
        }   
        break;
    case 3:
        for (int row = 0; row < 12; row++)
        {
            for (int column = 0; column < 16; column++)
            {
                map[row][column] = lvl3[row][column];
            }
        }   
        break;
    default:
        break;
    }
}

void Map::EntifyMap(Entities* entities)
{
    int type = 0;
    int coin;
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
                const char* platform_texture;
                if (map[row + 1][column] == 2)
                {
                    platform_texture = "assets/platform_ladder.bmp";
                }
                else if (map[row + 1][column] == 1)
                {
                    platform_texture = "assets/platform_stone.bmp";
                }
                else
                {
                    coin = rand() % 2;
                    if (coin == 1)
                    {
                        platform_texture = "assets/platform1.bmp";
                    }
                    else
                    {
                        platform_texture = "assets/platform2.bmp";
                    }
                }
                
                entities->CreateObject(platform_texture, x, y, 0, 'O', 1);
                break;
            case 2:
                const char* stairs_texture;

                coin = rand() % 2;
                if (coin == 1)
                {
                    stairs_texture = "assets/stairs1.bmp";
                }
                else
                {
                    stairs_texture = "assets/stairs2.bmp";
                }

                entities->CreateObject(stairs_texture, x, y, 0, 'S', 1);
                break;
            case 3:
                entities->CreateObject("assets/exit.bmp", x, y, 0, 'E', 1);
                break;
            default:
                break;
            }
        }
    }

    //window borders
    //entities->CreateObject("assets/dark.bmp", 0, 0 - Game::SCREEN_WIDTH, 0, 'W', (Game::SCREEN_WIDTH / 64)); // top
    entities->CreateObject("assets/dark.bmp", 0, Game::SCREEN_HEIGHT - 2, 0, 'W', (Game::SCREEN_WIDTH / 64)); // bottom
    entities->CreateObject("assets/dark.bmp", 0 - Game::SCREEN_HEIGHT + 2, 0, 0, 'W', (Game::SCREEN_HEIGHT / 64)); // left
    entities->CreateObject("assets/dark.bmp", Game::SCREEN_WIDTH - 2, 0, 0, 'W', (Game::SCREEN_HEIGHT / 64));  // right

    //entities->CreateObject("assets/cannon_sprite.bmp", 20, 127, 0, 'A', 1); // creating an antagonist
}

void Map::DestroyLevel(Entities* entities)
{
    int type = 0;

    for (int row = 0; row < 12; row++)
    {
        for (int column = 0; column < 16; column++)
        {
            type = map[row][column];

            switch (type)
            {
            case 1:
                entities->DestroyObjectByType('O');
                break;
            case 2:
                entities->DestroyObjectByType('S');
                break;
            case 3:
                entities->DestroyObjectByType('E');
                break;
            default:
                break;
            }
        }
    }

    //window borders
    //entities->DestroyObjectByType('W'); // top
    entities->DestroyObjectByType('W'); // bottom
    entities->DestroyObjectByType('W'); // left
    entities->DestroyObjectByType('W'); // right
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