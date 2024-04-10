#include "plant.h"

class grass: public plant
{
protected:
    
public:
    grass(world* world_point);

    void Action() override {};

    ~grass();
};

grass::grass(world* world_point): organizm(world_point)
{
}

grass::~grass()
{
}
