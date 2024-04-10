#include "animal.h"

class antelope: public animal
{   
public:
    antelope(world* world_point, YX position)
    :animal(4,4, position, world_point)
    {
        avatar = 'A';
    }

    void Action() override {};

    ~antelope();
};

antelope::~antelope()
{
}
