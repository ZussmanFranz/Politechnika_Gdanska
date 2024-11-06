#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include<SDL2/SDL.h>

#include "Game.hpp"

#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	768

int main(int argc, char* argv[])
{
    const int FPS = 60;
    const int frameDelay = (1000 / FPS);

    Uint32 frameStart;
    int frameTime;

    Game* game = new Game();

    game->init("Badya", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        
    }
    
    game->clean();

    return 0;
}