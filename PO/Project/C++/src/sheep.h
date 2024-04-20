#include "animal.h"

class sheep: public animal
{
public:
    sheep(world* world_point, YX position);

    //void Action() override {};

    ~sheep();
};
