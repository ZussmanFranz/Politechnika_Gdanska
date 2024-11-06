#include "turtle.h"
#include <cstdlib>

turtle::turtle(world* world_point, YX position)
:animal(2,1, position, world_point)
{
    avatar = 'T';
}

int turtle::Action() // 0 - normal move, 1 - collision detected
{
    if (rand() % 2 == 1) { // 0 - moving, 1 - not moving
        //world_point->GetLogger()->Log("turtle desided not to move\n");
        return 0;
    }

    int delta_y = rand() % 3 - 1; // Generates random number between -1 and 1
    int delta_x = rand() % 3 - 1; // Generates random number between -1 and 1

    if ((delta_x == 0) && (delta_y == 0)) {
        return 0;
    }

    return Move({delta_y, delta_x});
}

bool turtle::RejectAttak(organizm* attaker)
{
    if (attaker->GetStrength() < 5) {
        world_point->GetLogger()->Log("turtle rejected attak");
        return true;
    }

    return false;
}

organizm* turtle::MakeChild(YX new_position)
{
    return (new turtle(world_point, new_position));
}

turtle::~turtle()
{
}