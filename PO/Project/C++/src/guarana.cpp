#include "guarana.h"

guarana::guarana(YX position, world* world_point)
: plant(0, position ,world_point)
{
    avatar = 'u';
}

guarana::~guarana()
{
}