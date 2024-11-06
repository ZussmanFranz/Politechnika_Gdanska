#include "grass.h"

grass::grass(YX position, world* world_point)
: plant(0, position ,world_point)
{
    avatar = 'g';
}

organizm* grass::MakeChild(YX new_position)
{
    return (new grass(new_position, world_point));
}

grass::~grass()
{
}