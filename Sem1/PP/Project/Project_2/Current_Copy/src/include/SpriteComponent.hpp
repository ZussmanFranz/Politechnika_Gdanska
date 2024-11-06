#pragma once
#include "TextureManager.hpp"
#include <SDL2/SDL.h>

//OY frame numbers
const int RUN_RIGHT = 1; 
const int RUN_LEFT = 2;
const int FALL_RIGHT = 3;
const int FALL_LEFT = 4;
const int STATIC_RIGHT = 5;
const int STATIC_LEFT = 6;
const int STAIRS = 7;

const int ANIMATION_LENGTH = 6; //number of frames in the animation cycle

class SpriteComponent
{
private:
    SDL_Texture* texture;
public:
    char type;

    int state;
    int prev_state;
    int frame;

    SDL_Rect* scrRect;
    SDL_Rect* destRect;

    bool on_ground;
    bool on_stairs;
    bool brutally_murdered;
    bool exit;
    bool fire; //for antagoist

    SpriteComponent(SDL_Texture* tex, float scale, SDL_Rect* src, SDL_Rect* dest, char tp)
    {
        scrRect = src;
        destRect = dest;

        type = tp;

        (*scrRect).x = (*scrRect).y = 0;
        (*scrRect).w = (*scrRect).h = 64;

        frame = 1;
        state = 1;

        (*destRect).w = (*destRect).h = (int)((*scrRect).w * scale);

        texture = tex;

        prev_state = 1;

        if (type == 'A')
        {
            fire = false;
        }
    }

    void frame_update(float velocity_x, float velocity_y)
    {
        if ((type == 'B') || (type == 'A') || (type == 'G')) 
        {
            next_frame();
            state = 1;
        }
        else
        {
            if (on_stairs)
        {
            state = STAIRS;
        }
        else
        {
            if (velocity_x > 0)
            {
                if (on_ground)
                {
                    state = RUN_RIGHT;
                }
                else
                {
                    state = FALL_RIGHT;
                }
            }
            else if (velocity_x < 0)
            {
                if (on_ground)
                {
                    state = RUN_LEFT;
                }
                else
                {
                    state = FALL_LEFT;
                }
            }
            else
            {
                if ((prev_state == RUN_RIGHT) || (prev_state == FALL_RIGHT))
                {
                    state = STATIC_RIGHT;
                }
                else if ((prev_state == RUN_LEFT) || (prev_state == FALL_LEFT))
                {
                    state = STATIC_LEFT;
                }
            }
        }

        if (state == prev_state)
        {
            next_frame();
        }
        else
        {
            frame = 1;
        }

        prev_state = state;
        }
        
        //printf("%d\n", state);
        return;
    }

    void next_frame()
    {
        if ((frame + 1) > ANIMATION_LENGTH)
        {
            frame = 0;
        }
        frame++;
    }

    // bool animation_check(int temp_state, int state)
    // {
    //     if (temp_state == state)
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }

    void draw()
    {
        scrRect->x = scrRect->w * (frame - 1);
        scrRect->y = scrRect->h * (state - 1);

        TextureManager::Draw(texture, *scrRect, *destRect, frame);
    }

    ~SpriteComponent()
    {
        
    }
};

