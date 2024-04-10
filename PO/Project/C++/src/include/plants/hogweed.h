#include "plant.h"

class hogweed: public plant
{
protected:
    
public:
    hogweed(world* world_point);

    void Action() override {};

    ~hogweed();
};

hogweed::hogweed(world* world_point): organizm(world_point)
{
}

hogweed::~hogweed()
{
}
