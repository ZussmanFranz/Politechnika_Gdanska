#include "player.h"

player::player(world* world_point, YX position)
:animal(5,4, position, world_point)
{
    avatar = 'P';
}   

void player::Draw(YX position)
{
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    
    attron(COLOR_PAIR(1));
    
    mvaddch(position.y, position.x, avatar);
    
    attroff(COLOR_PAIR(1));
}


void player::Action(char input)
{
    YX delta = {0,0};

    switch (input)
    {
    case 'w':
        delta = {-1,0};
        break;
    case 'a':
        delta = {0,-1};
        break;
    case 's':
        delta = {1,0};
        break;
    case 'd':
        delta = {0,1};
        break;
    default:
        break;
    }

    Move(delta);
}

CLASS player::GetClass() 
{ 
    return PLAYER; 
}

player::~player()
{
}