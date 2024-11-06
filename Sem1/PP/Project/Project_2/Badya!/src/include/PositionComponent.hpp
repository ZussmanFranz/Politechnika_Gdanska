#pragma once
#include "SpriteComponent.hpp"
#include <math.h>

class PositionComponent
{
private:
    float xpos;
    float ypos;

    float init_xpos;
    float init_ypos;

    char type;
public:
    float velocity_x;
    float velocity_y;
    float gravity;
    int speed;
    
    SpriteComponent* sprite;

    PositionComponent(int x, int y, int sp, char type, SpriteComponent* spr)
    {
        xpos = x;
        ypos = y;
        init_xpos = x;
        init_ypos = y;
        
        velocity_x = 0;
        if ((type == 'B') || (type == 'G'))
        {
            velocity_x = 1;
        }
        velocity_y = 0;

        speed = sp;
        type = type;

        sprite = spr;
    }
    ~PositionComponent()
    {
        delete sprite;
    }

    int x() {return (int)xpos;}
    int y() {return (int)ypos;}

    void update()
    {
        // if (type == 'B')
        // {
        //     velocity_x = 1;
        // }
        
        xpos += velocity_x * speed;
        ypos += velocity_y * speed;

        if ((sprite->on_stairs == false) && (sprite->on_ground == false))
        {
            //printf("Gravity!!!\n");
            velocity_y += gravity;
        }

        if (sprite->on_stairs)
        {
            if (abs(velocity_y) < 1)
            {
                velocity_y = 0;
            }
            
            
        }
        
        // if (sprite->on_ground == true)
        // {
        //     //velocity_y = 0;
        //     printf("On ground\n");
        // }
        // else
        // {
        //     printf("Not on ground\n");
        // }

        if (sprite->brutally_murdered)
        {
            toInitPos();
            printf("Go home!!!\n");
            sprite->state = STATIC_RIGHT;
            sprite->brutally_murdered = false;
        }
        
    }

    void setPos(int x, int y)
    {
        xpos = x;
        ypos = y;
    }

    void toInitPos()
    {
        xpos = init_xpos;
        ypos = init_ypos;
    }

    void Push(float dx, float dy)
    {
        xpos += dx;
        ypos += dy;
    }
};

