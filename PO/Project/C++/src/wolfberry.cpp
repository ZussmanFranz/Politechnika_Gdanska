#include "wolfberry.h"

wolfberry::wolfberry(YX position, world* world_point)
: plant(99, position ,world_point)
{
    avatar = 'w';
}

organizm* wolfberry::MakeChild(YX new_position)
{
    return (new wolfberry(new_position, world_point));
}

wolfberry::~wolfberry()
{
}