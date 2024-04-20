#include "fox.h"

fox::fox(world* world_point, YX position)
:animal(4,4, position, world_point)
{
    avatar = 'F';
}

fox::~fox()
{
}
