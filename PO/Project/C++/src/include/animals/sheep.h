#include "animal.h"

class sheep: public animal
{
public:
    sheep(world* world_point, YX position)
    :animal(4,4, position, world_point)
    {
        avatar = 'S';
    }

    void Action() override {};

    ~sheep();
};

sheep::~sheep()
{
}
