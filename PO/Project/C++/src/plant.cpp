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
        wattron(world_point->GetWindow(),A_BOLD); 
    }

    wattron(world_point->GetWindow(),COLOR_PAIR(2));
    
    mvwaddch(world_point->GetWindow(),position.y, position.x, avatar);
    
    wattroff(world_point->GetWindow(),COLOR_PAIR(2));

    if (strength > starting_strength) 
    {
        wattroff(world_point->GetWindow(),A_BOLD); 
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