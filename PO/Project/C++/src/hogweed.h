#include "plant.h"

class hogweed: public plant
{
public:
    hogweed(YX position, world* world_point);

    organizm* MakeChild(YX new_position) override;

    ~hogweed();
};
