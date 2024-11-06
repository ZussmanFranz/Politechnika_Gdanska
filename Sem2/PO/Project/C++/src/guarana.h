#include "plant.h"

class guarana: public plant
{
public:
    guarana(YX position, world* world_point);

    bool RejectAttak(organizm* attaker);

    organizm* MakeChild(YX new_position) override;

    ~guarana();
};
