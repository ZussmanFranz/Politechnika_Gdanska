#include "antelope.h"

antelope::antelope(world* world_point, YX position)
:animal(4,4, position, world_point)
{
    avatar = 'A';
}

antelope::~antelope()
{
}