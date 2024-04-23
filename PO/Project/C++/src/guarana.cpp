#include "guarana.h"

guarana::guarana(YX position, world* world_point)
: plant(0, position ,world_point)
{
    avatar = 'u';
}

organizm* guarana::MakeChild(YX new_position)
{
    return (new guarana(new_position, world_point));
}

guarana::~guarana()
{
}