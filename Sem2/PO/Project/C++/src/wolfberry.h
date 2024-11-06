#include "organizm.h"
#include "plant.h"

class wolfberry: public plant
{
public:
    wolfberry(YX position, world* world_point);

    bool RejectAttak(organizm* attaker) override;

    organizm* MakeChild(YX new_position) override;

    ~wolfberry();
};
