#include "plant.h"
#include <cstdlib>

plant::plant(int strength, YX position, world* world_point)
: organizm(world_point)
{
    this->strength = strength;
    this->initiative = 0;
    this->position = position;
}

void plant::Draw(YX position)
{   
    attron(COLOR_PAIR(2));
    
    mvaddch(position.y, position.x, avatar);
    
    attroff(COLOR_PAIR(2));
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