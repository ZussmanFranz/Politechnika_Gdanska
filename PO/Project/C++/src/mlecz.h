#include "plant.h"

class mlecz: public plant
{
public:
    mlecz(YX position, world* world_point);

    int Action() override;
    organizm* MakeChild(YX new_position) override;

    ~mlecz();
};
