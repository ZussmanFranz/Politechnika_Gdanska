#include "hogweed.h"
#include <vector>

hogweed::hogweed(YX position, world* world_point)
: plant(10, position ,world_point)
{
    avatar = 'h';
}

int hogweed::Action()
{
    if (rand() % 50 == 0) {
        Reproduct();
        //return 0;
    }

    //kill neighbours
    std::vector<field*> near = world_point->GetFieldsNear(position);

    for (int i = 0; i < near.size(); i++) 
    {
        if (near[i]->member != nullptr) 
        {
            world_point->GetLogger()->Log("hogweed killed an organizm with the area attak");
            world_point->Destroy(near[i]->member);
        }
    }
    
    return 1;
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