#include "wolf.h"

wolf::wolf(world* world_point, YX position)
:animal(9,5, position, world_point)
{
    avatar = 'W';
}

wolf::~wolf()
{
}
