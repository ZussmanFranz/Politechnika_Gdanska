#include "grass.h"

grass::grass(YX position, world* world_point)
: plant(0, position ,world_point)
{
    avatar = 'g';
}

grass::~grass()
{
}