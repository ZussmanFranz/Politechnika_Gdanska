#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PositionComponent.hpp"

class KeyboardController
{
private:
    
public:
    KeyboardController(PositionComponent* pos)
    {
        position = pos;
    }
    ~KeyboardController();

    PositionComponent* position;

    void update()
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                position->velocity_y = -1;
                break;
            case SDLK_d:
                position->velocity_x = 1;
                break;
            case SDLK_s:
                position->velocity_y = 1;
                break;
            case SDLK_a:
                position->velocity_x = -1;
                break;
<<<<<<< HEAD
            case SDLK_SPACE:
                if (sprite->on_ground)
                {
                    position->velocity_y = -1.8;
                    sprite->on_ground = false;
                }
                break;
=======
>>>>>>> parent of a5a0ea7 (PP jumps almost done)
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

