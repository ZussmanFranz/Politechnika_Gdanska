#include "animal.h"
#include "organizm.h"

class wolf: public animal
{  
public:
    wolf(world* world_point, YX position);

    organizm* MakeChild(YX new_position) override;

    ~wolf();
};