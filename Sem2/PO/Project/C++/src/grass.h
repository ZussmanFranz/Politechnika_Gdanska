#include "plant.h"

class grass: public plant
{
public:
    grass(YX position, world* world_point);

    organizm* MakeChild(YX new_position) override;

    ~grass();
};
