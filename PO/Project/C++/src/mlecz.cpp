#include "mlecz.h"

mlecz::mlecz(YX position, world* world_point)
: plant(0, position ,world_point)
{
    avatar = 'm';
}

mlecz::~mlecz()
{
}