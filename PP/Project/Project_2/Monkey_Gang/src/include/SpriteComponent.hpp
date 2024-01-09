#pragma once
#include "TextureManager.hpp"
#include <SDL2/SDL.h>

const int STATIC = 1;
const int RUN_RIGHT = 2;
const int RUN_LEFT = 3;
const int FALL_RIGHT = 4;
const int FALL_LEFT = 5;
const int STAIRS = 6;

const int ANIMATION_LENGTH = 6;

const int PLAYER_STATIC = 2;
const int PLAYER_RIGHT_FRAME_1 = 1;
const int PLAYER_LEFT_FRAME_1 = 7;
const int PLAYER_FALL_RIGHT_FRAME = 4;
const int PLAYER_FALL_LEFT_FRAME = 10;
const int PLAYER_STAIRS_FRAME_1 = 14;

const int BADYA_FRAME_1 = 1;

class SpriteComponent
{
private:
    SDL_Texture* texture;

    int frame;
    int state;
    int temp_state;
public:
    SDL_Rect* scrRect;
    SDL_Rect* destRect;

    SpriteComponent(SDL_Texture* tex, float scale, SDL_Rect* src, SDL_Rect* dest)
    {
        scrRect = src;
        destRect = dest;

        (*scrRect).x = (*scrRect).y = 0;
        (*scrRect).w = (*scrRect).h = 64;

        frame = 1;

        (*destRect).w = (*destRect).h = (int)((*scrRect).w * scale);

        texture = tex;
    }

    /*void frame_update()
    {
        bool anim = animation_check(temp_state, state);
        state = temp_state;

        switch (state)
        {
        case STATIC :
            frame = PLAYER_STATIC;
            break;
        case RUN_LEFT :
            if (anim)
            {
                animation(frame, PLAYER_LEFT_FRAME_1);
            }
            else
            {
                frame = PLAYER_LEFT_FRAME_1;
            }
            break;
        case RUN_RIGHT :
        if (anim)
            {
                animation(frame, PLAYER_RIGHT_FRAME_1);
            }
            else
            {
                frame = PLAYER_RIGHT_FRAME_1;
            }
            break;
        case FALL_LEFT :
            frame = PLAYER_FALL_LEFT_FRAME;
            break;
        case FALL_RIGHT :
            frame = PLAYER_FALL_RIGHT_FRAME;
            break;
        //case stairs
        default:
            break;
        }
    }

    void animation(int frame, int starting_frame)
    {
        if ((frame + 1) > ANIMATION_LENGTH)
        {
            frame = starting_frame;
        }
        frame++;
    }

    bool animation_check(int temp_state, int state)
    {
        if (temp_state == state)
        {
            return true;
        }
        else
        {
            return false;
        }
    }*/

    void draw()
    {
        //printf("srcRect: x: %d, y: %d, w: %d, h: %d\n destRect: x: %d, y: %d, w: %d, h: %d\n frame: %d \n", (*scrRect).x, (*scrRect).y, (*scrRect).w, (*scrRect).h, (*destRect).x, (*destRect).y, (*destRect).w, (*destRect).h, frame);
        TextureManager::Draw(texture, *scrRect, *destRect, frame);
    }

    ~SpriteComponent();
};

