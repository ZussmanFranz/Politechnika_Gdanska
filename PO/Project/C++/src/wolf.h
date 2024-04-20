#include "animal.h"

class wolf: public animal
{  
public:
    wolf(world* world_point, YX position);

    //void Action() override;

    ~wolf();
};