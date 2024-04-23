#include "organizm.h"
#include "plant.h"

class wolfberry: public plant
{
public:
    wolfberry(YX position, world* world_point);

    organizm* MakeChild(YX new_position) override;

    ~wolfberry();
};
