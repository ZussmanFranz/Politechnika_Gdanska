#include "plant.h"

class guarana: public plant
{
protected:
    
public:
    guarana(world* world_point);

    void Action() override {};

    ~guarana();
};

guarana::guarana(world* world_point): organizm(world_point)
{
}

guarana::~guarana()
{
}
