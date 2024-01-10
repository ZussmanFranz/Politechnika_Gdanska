#include "Game.hpp"
//#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "SpriteComponent.hpp"
#include "Entities.hpp"

Entities* entities;
GameObject** game_objects;

GameObject* player;
GameObject* badya;

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

int dx, dy;

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

    entities = new Entities();

    if (entities != NULL)
    {
        printf("Entities initialised!\n");
    }
    
    game_objects = entities->GetObjects();

    map = new Map();
    map->EntifyMap(entities); //first, we add "decorations";

    player = new GameObject("assets/dwarf_sprite.bmp", 0, Game::SCREEN_HEIGHT - 112, PLAYER_SPEED, 'P', PLAYER_SCALE);
    player->keyboard = new KeyboardController(player->position,player->sprite);
    entities->AppendObject(player);

    badya = new GameObject("assets/badya_sprite.bmp", 20, 20, BADYA_SPEED, 'B', BADYA_SCALE);
    entities->AppendObject(badya);
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    
    if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            }
        }
    else if (event.type == SDL_QUIT)
    {
        isRunning = false;
    }

    player->keyboard->update();
}

void Game::update()
{
    entities->UpdateObjects();
    if (player->sprite->exit)
    {
        finish();
    }
    
}

void Game::render()
{
    SDL_RenderClear(renderer);

    TextureManager::DrawBackground();

    entities->RenderObjects();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game cleaned\n");
}

void Game::finish()
{
    //finish level
    isRunning = false;
}