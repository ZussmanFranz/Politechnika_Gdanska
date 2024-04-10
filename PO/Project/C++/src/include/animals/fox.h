#include "animal.h"

class fox: public animal
{
public:
    fox(world* world_point, YX position)
    :animal(4,4, position, world_point)
    {
        avatar = 'F';
    }
    
    void Action() override {};

    ~fox();
};

fox::~fox()
{
}
