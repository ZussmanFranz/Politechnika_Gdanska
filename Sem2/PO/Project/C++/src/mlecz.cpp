#include "mlecz.h"

mlecz::mlecz(YX position, world* world_point)
: plant(0, position ,world_point)
{
    avatar = 'm';
}

int mlecz::Action()
{
    int result = 1;

    for (int i = 0; i < 3; i++) 
    {   
        if (rand() % 50 == 0) {
            Reproduct();
            result = 0;
        }   
    }
    
    return result;
}

organizm* mlecz::MakeChild(YX new_position)
{
    return (new mlecz(new_position, world_point));
}

mlecz::~mlecz()
{
}