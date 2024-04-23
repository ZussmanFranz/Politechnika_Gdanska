#include "sheep.h"

sheep::sheep(world* world_point, YX position)
:animal(4,4, position, world_point)
{
    avatar = 'S';
}

organizm* sheep::MakeChild(YX new_position)
{
    return (new sheep(world_point, new_position));
}

sheep::~sheep()
{
}