#include "turtle.h"

turtle::turtle(world* world_point, YX position)
:animal(2,1, position, world_point)
{
    avatar = 'T';
}

turtle::~turtle()
{
}