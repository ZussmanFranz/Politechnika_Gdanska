#include "animal.h"

class antelope: public animal
{   
public:
    antelope(world* world_point, YX position);

    int Action() override;
    bool RejectAttak(organizm* attaker) override;

    ~antelope();
};

