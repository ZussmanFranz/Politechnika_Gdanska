#include "plant.h"

class mlecz: public plant
{
protected:
    
public:
    mlecz(world* world_point);

    void Action() override {};

    ~mlecz();
};

mlecz::mlecz(world* world_point): organizm(world_point)
{
}

mlecz::~mlecz()
{
}
