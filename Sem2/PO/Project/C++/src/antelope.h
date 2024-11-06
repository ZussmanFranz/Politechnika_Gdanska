#include "animal.h"

class antelope: public animal
{   
public:
    antelope(world* world_point, YX position);

    int Action() override;
    bool RejectAttak(organizm* attaker) override;
    organizm* MakeChild(YX new_position) override;

    ~antelope();
};

