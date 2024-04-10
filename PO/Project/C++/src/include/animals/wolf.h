#include "animal.h"

class wolf: public animal
{  
public:
    wolf(world* world_point, YX position)
    :animal(9,5, position, world_point)
    {
        avatar = 'W';
    }

    void Action() override {};

    ~wolf();
};

wolf::~wolf()
{
}
