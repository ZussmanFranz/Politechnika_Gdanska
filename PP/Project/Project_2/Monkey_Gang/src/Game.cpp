#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"

GameObject* player;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    cnt = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        printf("Subsystems initialised!...\n");
        
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window)
        {
            printf("Window created!\n");
        }
        
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            printf("Renderer created!\n");
        }
        
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    player = new GameObject("assets/dwarf_sprite_running.bmp", renderer);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}

void Game::update()
{
    player->Update();
}

void Game::render()
{
    SDL_RenderClear(renderer);

    player->Render();

    SDL_RenderPresent(renderer);

}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game cleaned\n");
}