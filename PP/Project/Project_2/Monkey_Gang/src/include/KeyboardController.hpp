#pragma once

#include "Game.hpp"
//#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PositionComponent.hpp"

class KeyboardController
{
public:
    KeyboardController(PositionComponent* pos, SpriteComponent* spr)
    {
        position = pos;
        sprite = spr;
    }
    ~KeyboardController();

    PositionComponent* position;
    SpriteComponent* sprite;

    void update()
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                if (sprite->on_stairs)
                {
                    position->velocity_y = -1;   
                }
                break;
            case SDLK_d:
                position->velocity_x = 1;
                break;
            case SDLK_s:
                if (sprite->on_stairs)
                {
                    position->velocity_y = 1;   
                }
                break;
            case SDLK_a:
                position->velocity_x = -1;
                break;
            case SDLK_SPACE:
                position->velocity_y = -1.8;
                sprite->on_ground = false;
                break;
            default:
                break;
            }
        }
        
        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                position->velocity_y = 0;
                break;
            case SDLK_d:
                position->velocity_x = 0;
                break;
            case SDLK_s:
                position->velocity_y = 0;
                break;
            case SDLK_a:
                position->velocity_x = 0;
                break;
            default:
                break;
            }
        }
        
    }
};

