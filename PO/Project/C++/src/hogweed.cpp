#include "hogweed.h"

hogweed::hogweed(YX position, world* world_point)
: plant(10, position ,world_point)
{
    avatar = 'h';
}

organizm* hogweed::MakeChild(YX new_position)
{
    return (new hogweed(new_position, world_point));
}

hogweed::~hogweed()
{
}