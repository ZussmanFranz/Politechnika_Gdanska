#include "plant.h"
#include <cstdlib>

plant::plant(int strength, YX position, world* world_point)
: organizm(world_point, strength, 0, position)
{
}

void plant::Draw(YX position)
{   
    if (strength > starting_strength) 
    {
        attron(A_BOLD); 
    }

    attron(COLOR_PAIR(2));
    
    mvaddch(position.y, position.x, avatar);
    
    attroff(COLOR_PAIR(2));

    if (strength > starting_strength) 
    {
        attroff(A_BOLD); 
    }
}

int plant::Action()
{
    if (rand() % 50 == 0) {
        Reproduct();
        return 0;
    }
    
    return 1;
}


plant::~plant()
{
}