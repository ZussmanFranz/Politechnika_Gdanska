#include "guarana.h"

guarana::guarana(YX position, world* world_point)
: plant(0, position ,world_point)
{
    avatar = 'u';
}

bool guarana::RejectAttak(organizm* attaker)
{
    attaker->SetStrength(attaker->GetStrength() + 3);

    world_point->GetLogger()->LogStrengthIncrease(attaker);

    return false;
}

organizm* guarana::MakeChild(YX new_position)
{
    return (new guarana(new_position, world_point));
}

guarana::~guarana()
{
}