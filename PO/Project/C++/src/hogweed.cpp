#include "hogweed.h"

hogweed::hogweed(YX position, world* world_point)
: plant(10, position ,world_point)
{
    avatar = 'h';
}

bool hogweed::RejectAttak(organizm* attaker)
{
    attaker->IAmEddarOfHouseStartkLordOfWinterfellAndWardenOfTheNorthSentenceYouToDie();

    world_point->GetLogger()->Log("hogweed instantly killed an attaker");

    return true;
}

organizm* hogweed::MakeChild(YX new_position)
{
    return (new hogweed(new_position, world_point));
}

hogweed::~hogweed()
{
}