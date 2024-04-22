#include "wolfberry.h"

wolfberry::wolfberry(YX position, world* world_point)
: plant(99, position ,world_point)
{
    avatar = 'w';
}

wolfberry::~wolfberry()
{
}