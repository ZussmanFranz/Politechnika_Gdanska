#include "mlecz.h"

mlecz::mlecz(YX position, world* world_point)
: plant(0, position ,world_point)
{
    avatar = 'm';
}

organizm* mlecz::MakeChild(YX new_position)
{
    return (new mlecz(new_position, world_point));
}

mlecz::~mlecz()
{
}