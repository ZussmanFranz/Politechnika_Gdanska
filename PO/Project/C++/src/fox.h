#include "animal.h"

class fox: public animal
{
public:
    fox(world* world_point, YX position);
    
    int Fight(organizm* target) override; 

    ~fox();
};

