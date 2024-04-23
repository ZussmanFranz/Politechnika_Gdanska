#include "animal.h"

class sheep: public animal
{
public:
    sheep(world* world_point, YX position);

    organizm* MakeChild(YX new_position) override;

    ~sheep();
};
