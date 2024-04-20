#include "plant.h"

class wolfberry: public plant
{
protected:
    
public:
    wolfberry(world* world_point);

    void Action() override {};

    ~wolfberry();
};

wolfberry::wolfberry(world* world_point): organizm(world_point)
{
}

wolfberry::~wolfberry()
{
}
