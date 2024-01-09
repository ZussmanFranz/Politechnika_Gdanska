#pragma once
#include "SpriteComponent.hpp"

class PositionComponent
{
private:
    float xpos;
    float ypos;

    char type;
public:
    float velocity_x;
    float velocity_y;
    int speed;
    
    PositionComponent(int x, int y, int sp, char type)
    {
        xpos = x;
        ypos = y;
        
        velocity_x = 0;
        if (type == 'B')
        {
            velocity_x = 1;
        }
        velocity_y = 0;

        speed = sp;
        type = type;
    }
    ~PositionComponent();

    int x() {return (int)xpos;}
    int y() {return (int)ypos;}

    void update()
    {
        xpos += velocity_x * speed;
        ypos += velocity_y * speed;
    }

    void setPos(int x, int y)
    {
        xpos = x;
        ypos = y;
    }

    void Push(float dx, float dy)
    {
        xpos += dx;
        ypos += dy;
    }
};

