#include "wolf.h"

wolf::wolf(world* world_point, YX position)
:animal(9,5, position, world_point)
{
    avatar = 'W';
}

organizm* wolf::MakeChild(YX new_position)
{
    return (new wolf(world_point, new_position));
}

wolf::~wolf()
{
}
