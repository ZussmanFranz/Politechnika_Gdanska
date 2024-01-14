#include "Game.hpp"
//#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "SpriteComponent.hpp"
#include "Entities.hpp"

Entities* entities;
GameObject** game_objects;

GameObject* player;
GameObject* antagonist;

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

int Game::level = 1;

Uint32 Game::SkipTime = 0;
Uint32 Game::WorldTime = 0;
Uint32 Game::FinishTime = 0;

Uint32 Game::delta_B = 0;
Uint32 Game::delta_A = 36; // starts with 36 frames prediction (35 + 1 to switch frame)
Uint32 Game::delta_Frame = 0;

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

    //level = 1;

    map = new Map();
    map->LoadMap(level);
    map->EntifyMap(entities); //first, we add "decorations";

    player = new GameObject("assets/dwarf_sprite.bmp", 2, Game::SCREEN_HEIGHT - 64, PLAYER_SPEED, 'P', PLAYER_SCALE);
    player->keyboard = new KeyboardController(player->position,player->sprite);
    entities->AppendObject(player);

    antagonist = new GameObject("assets/cannon_sprite.bmp", BADYA_SPAWN_X - (64 * BADYA_SCALE), BADYA_SPAWN_Y, 0, 'A', 1); // creating an antagonist
    entities->AppendObject(antagonist);

    entities->CreateObject("assets/badya_sprite.bmp", BADYA_SPAWN_X, BADYA_SPAWN_Y, BADYA_SPEED, 'B', BADYA_SCALE);

    TextureManager::InitWriting("assets/cs8x8.bmp");
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
            case SDLK_1:
                load(1);
                break;
            case SDLK_2:
                load(2);
                break;
            case SDLK_3:
                load(3);
                break;
            case SDLK_n:
                SkipTime = WorldTime;
                player->position->toInitPos();
                player->sprite->state = STATIC_RIGHT;
                entities->DestroyAllObjectsByType('B');
                break;
            default:
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

    Game::delta_A++;
    Game::delta_B++;
    Game::delta_Frame++;

    //printf("Delta B: (%d), Delta Frames: (%d)\n", delta_B, delta_Frame);

    if (delta_A >= BADYA_DELAY)
    {
        antagonist->sprite->fire = true;
        Game::delta_A = 0; 
    }
    
    if (delta_B >= BADYA_DELAY) // co ? sekund
    {
        antagonist->sprite->fire = false;
        entities->CreateObject("assets/badya_sprite.bmp", BADYA_SPAWN_X, BADYA_SPAWN_Y, BADYA_SPEED, 'B', BADYA_SCALE);
        Game::delta_B = 0;
    }

    if (delta_Frame >= NEW_FRAME_DELAY) // co 0,1 sekund
    {
        entities->UpdateFrames();
        Game::delta_Frame = 0;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    TextureManager::DrawBackground();
    WorldTime = SDL_GetTicks();
    TextureManager::DrawInfo(WorldTime - SkipTime);

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

void Game::load(int lvl)
{
    Game::level = lvl;
    printf("Starting loading lvl %d\n", level);
    //map->DestroyLevel(entities);

    map->DestroyLevel(entities);
    entities->DestroyAllObjectsByType('B');

    map->LoadMap(level);
    map->EntifyMap(entities);

    //entities->TossPlayer();
    player->position->toInitPos();
}

void Game::finish()
{
    player->sprite->exit = false;
    if (level < number_of_levels)
    {
        level++;
        load(level);
    }
    else
    {
        isRunning = true;

        FinishTime = (WorldTime - SkipTime) / 1000;

        while (isRunning)
        {
            SDL_RenderClear(renderer);
            TextureManager::DrawOutro(FinishTime);
            SDL_RenderPresent(Game::renderer);

            handleEvents();
        }
    }
}