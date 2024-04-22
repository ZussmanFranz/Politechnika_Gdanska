#include "player.h"

player::player(world* world_point, YX position)
:animal(5,4, position, world_point)
{
    avatar = 'P';
}   

void player::Draw(YX position)
{   
    attron(COLOR_PAIR(3));
    
    mvaddch(position.y, position.x, avatar);
    
    attroff(COLOR_PAIR(3));
}


int player::Action()
{
    YX delta = {0,0};

    char input = getch();

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
    case 'q':
        world_point->StopIt();
        break;
    default:
        break;
    }

    return Move(delta);
}

CLASS player::GetClass() 
{ 
    return PLAYER; 
}

player::~player()
{
}