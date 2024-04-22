#include "plant.h"

class wolfberry: public plant
{
protected:
    
public:
    wolfberry(world* world_point);

    int Action() override {};

    ~wolfberry();
};