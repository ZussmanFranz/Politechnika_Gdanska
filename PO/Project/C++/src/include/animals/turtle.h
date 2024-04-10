#include "animal.h"

class turtle:public animal
{
protected:
    
public:
    turtle(world* world_point, YX position)
    :animal(2,1, position, world_point)
    {
        avatar = 'T';
    }

    void Action() override {};
    
    ~turtle();
};

turtle::~turtle()
{
}
