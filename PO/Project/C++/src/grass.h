#include "plant.h"

class grass: public plant
{
public:
    grass(YX position, world* world_point);

    //int Action() override {};

    ~grass();
};
