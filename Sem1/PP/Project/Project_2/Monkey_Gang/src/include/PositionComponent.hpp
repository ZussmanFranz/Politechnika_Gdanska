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
<<<<<<< HEAD
    float gravity;

=======
>>>>>>> parent of a5a0ea7 (PP jumps almost done)
    int speed;

    int deep_x;
    int deep_y;
    
    PositionComponent(int x, int y, int sp, char type)
    {
        xpos = x;
        ypos = y;
<<<<<<< HEAD
        init_xpos = x;
        init_ypos = y;


=======
>>>>>>> parent of a5a0ea7 (PP jumps almost done)
        
        velocity_x = 0;
        if (type == 'B')
        {
            velocity_x = 1;
        }
        velocity_y = 0;

        speed = sp;
        type = type;
<<<<<<< HEAD

        sprite = spr;

        deep_x = 0;
        deep_y = 0;
=======
>>>>>>> parent of a5a0ea7 (PP jumps almost done)
    }
    ~PositionComponent();

    int x() {return (int)xpos;}
    int y() {return (int)ypos;}

    void update()
    {
<<<<<<< HEAD
        /*if (type == 'B')
        {
            velocity_x = 1;
        }*/
        
        xpos += velocity_x * speed;
        ypos += velocity_y * speed;

        if (sprite->on_ground)
        {
            velocity_y = 0;
        }
        

        if ((sprite->on_stairs == false) && (sprite->on_ground == false))
        {
            velocity_y += gravity;
        }
        

        if (sprite->brutally_murdered)
        {
            toInitPos();
            printf("Go home!!!\n");
            sprite->brutally_murdered = false;
        }
        
=======
        xpos += velocity_x * speed;
        ypos += velocity_y * speed;
>>>>>>> parent of a5a0ea7 (PP jumps almost done)
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

