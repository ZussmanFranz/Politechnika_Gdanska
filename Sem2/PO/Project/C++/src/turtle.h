#include "animal.h"

class turtle:public animal
{
protected:
    
public:
    turtle(world* world_point, YX position);

    int Action() override;
    bool RejectAttak(organizm* attaker) override;
    organizm* MakeChild(YX new_position) override;
    
    ~turtle();
};
