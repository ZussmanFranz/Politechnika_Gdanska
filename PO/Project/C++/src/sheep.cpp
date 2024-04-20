#include "sheep.h"

sheep::sheep(world* world_point, YX position)
:animal(4,4, position, world_point)
{
    avatar = 'S';
}

sheep::~sheep()
{
}