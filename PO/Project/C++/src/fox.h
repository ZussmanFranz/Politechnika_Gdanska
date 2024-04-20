#include "animal.h"

class fox: public animal
{
public:
    fox(world* world_point, YX position);
    
    //void Action() override {};

    ~fox();
};

