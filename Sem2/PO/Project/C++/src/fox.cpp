#include "fox.h"

fox::fox(world* world_point, YX position)
:animal(4,4, position, world_point)
{
    avatar = 'F';
}

int fox::Fight(organizm* target)
{
    if (target->GetStrength() > strength)
    {
        world_point->GetLogger()->Log("fox avoided the fight");

        world_point->FindField(position)->member = this;

        return 1;
    }
    
    return animal::Fight(target);
}

organizm* fox::MakeChild(YX new_position)
{
    return (new fox(world_point, new_position));
}

fox::~fox()
{
}
