#include "plant.h"

class hogweed: public plant
{
public:
    hogweed(YX position, world* world_point);

    bool RejectAttak(organizm* attaker) override;

    organizm* MakeChild(YX new_position) override;

    ~hogweed();
};
