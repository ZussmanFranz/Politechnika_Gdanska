#include "plant.h"

plant::plant(int strength, YX position, world* world_point)
: organizm(world_point)
{
    this->strength = strength;
    this->initiative = 0;
    this->position = position;
}

void plant::Draw(YX position)
{
    init_pair(1, COLOR_GREEN, -1);
    
    attron(COLOR_PAIR(1));
    
    mvaddch(position.y, position.x, avatar);
    
    attroff(COLOR_PAIR(1));
}

int plant::Action()
{
    //rozmnażanie
    return 0;
}

plant::~plant()
{
}