#pragma once
#include "animal.h"

class player: public animal
{  
public:
    player(world* world_point, YX position);

    void Draw(YX position) override;
    int Action() override;
    organizm* MakeChild(YX new_position) override;

    CLASS GetClass() override;

    ~player();
};
